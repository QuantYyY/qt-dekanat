#include "corner.h"
#include "ui_corner.h"
#include "mainwindow.h"
#include <math.h>

void changeSaveFile(QString str1, double tz1)
{
    QFile file("file.csv");
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QString str = file.readAll();
        file.resize(0);
        str.replace("Первый шаг резания в забойной части; " + str1, "Первый шаг резания в забойной части; " + changeDot(QString::number(tz1)));
        QTextStream stream(&file);
        stream << str;
        file.close();
    }
}

Corner::Corner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Corner)
{
    ui->setupUi(this);
}

Corner::~Corner()
{
    delete ui;
}

void Corner::doSomthing()
{
    tz.push_back(tzz);
    strok1 = "Крайний шаг резания; " + changeDot(QString::number(tzz)) + '\n';
    strok1 += "Длина забойной части исполнительного органа; " + changeDot(QString::number(bzz)) + '\n';
}

void Corner::lengthLine()
{
    tz.push_back(tz1);
    for (int ilz = 2; ilz < nlz; ilz++)
    {
        float tzzbuffer = (((tz1 - tk1)*(ilz - 1))/(nlz -1) + tz1);
        tz.push_back(tzzbuffer);
        sumtz += tzzbuffer;
        window.setLengthLine(ilz, tzzbuffer);
        strok += "Шаг резания забойной части для линии резания " + QString::number(ilz) + "; " + changeDot(QString::number(tzzbuffer)) + '\n';
        maxsumtz = sumtz;
    }
}

void Corner::setFields(double maxsumtk, std::vector<double> tk2, double lkk, double sigma)
{
    this->maxsumtk = maxsumtk;
    this->tk2 = tk2;
    this->lkk = lkk;
    this->sigma = sigma;
}

void Corner::calculateSum()
{
    for (int i = 0; i < tk2.size(); i++)
    {
        sum = sum + tk2[i];
        double t = ((lkk+lxb)*sin(sigma))*180/PI;
        double t1 = (bzk - sum);
        double buffer = round(0.85*asin((bzk - sum)/((lkk+lxb)*sin(sigma)))*180/PI);
        if(buffer != buffer)
        {
            QMessageBox::warning(this, "Error", "Некорретные данные");
            throw 1;
        }
        betta.push_back(buffer);
    }
}

void Corner::calculateCorner()
{
    QString string;
    for (int i = 0 ; i < betta.size(); i++)
    {
        window.setTextBrowser(i+1, betta[i]);
        string += "Угол наклона резца к направлению подачи для линии резания " + QString::number(i+1) + "; " + changeDot(QString::number(betta[i])) + '\n';
    }
    saveDataInFile(string);
}

void Corner::saveData()
{
    QString str = "Длина хвостовика куткового резца; " + ui->doubleSpinBox->text() + '\n';
    str += "Длина кутковой части исполнительного органа; " + changeDot(QString::number(bzk)) + '\n';
    str += "Количество линий резания для забойной части; " + changeDot(QString::number(nlz)) + '\n';
    saveDataInFile(str);
}

void Corner::changeFields()
{
    lxb = ui->doubleSpinBox->value();
    tzz = ui->doubleSpinBox_2->value();

    if(topt == 0)
    {
        topt = findDouble(*(new QString("Средняя оптимальная ширина стружки для забойных резцов")));
        b = findDouble(*(new QString("Ширина захвата")));
        tz1 = findDouble(*(new QString("Первый шаг резания в забойной части")));
        tk1 = findDouble(*(new QString("Крайний кутковый шаг резания")));
    }

    bzk = round(maxsumtk*10)/10;
    nlz = round(((100.0 * b) - bzk)/topt);
    if(maxsumtz == 0)
    {
        for (int ilz = 2; ilz < nlz; ilz++)
        {
            float tzzbuffer = (((tz1 - tk1)*(ilz - 1))/(nlz -1) + tz1);
            sumtz += tzzbuffer;
            maxsumtz = sumtz;
        }
    }
    bzz = (round(maxsumtz*10)/10) + (round(tzz*10)/10)+tz1;
    qDebug() << "IT_GANG";
}

void Corner::clickTwo(QString& tz1s, QString& tzzs)
{
    double tzi;
    tz.push_back(tz1);
    tz.push_back(tzz);
    for (int ilz = 2; ilz < nlz; ilz++)
    {
        tzi = round((((tz1 - tk1)*(ilz - 1))/(nlz -1) + tz1)*10)/10;
        tz.push_back(tzi);
        sumtz += tzi;
        window.setLengthLine(ilz, tzi);
        strok += "Шаг резания забойной части для линии резания  " + QString::number(ilz) +  "; " + changeDot(QString::number(tzi)) + '\n';
        maxsumtz = sumtz;

    }
    sumtz = 0;
    bzz = maxsumtz + (round(tzz*10)/10)+tz1;
    strok1 += "Краний шаг резания; " + changeDot(QString::number(tzz)) + '\n';

    strok1 += "Длина забойной части исполнительного органа; " + changeDot(QString::number(bzz)) + '\n';

    //std::cout << "Необходимое условие для длины забойной части : " << 100.0 * b - bzk << " <= "<< bzz << " <= " << 100.0*b + topt - bzk << std::endl;
    if (!((100*b <= (bzz+bzk)) && (100*b+1.5 >=(bzz+bzk))))
    {
        window.setTextBrowser(*(new QString("Длина линии резания")));
        strok = "";
        strok1 = "";
        tz.clear();
        QMessageBox::warning(this, "Error", "Выполните перерасчет, уменьшите(увеличьте) значение крайнего шага резания или первого шага резания");
        ed.set(tz1, tzz);

        ed.show();
        st = Status::Two;
        return;
    }
    window.setVector(&tz);
    changeSaveFile(tz1s, tz1);
    saveDataInFile(strok);
    saveDataInFile(strok1);
    window.show();
    this->close();
}

void Corner::on_pushButton_clicked()
{
    if(st == Status::One)
    {
        changeFields();

        if(lxb == 0 || 1.15*topt < tzz)
        {
            QMessageBox::warning(this, "Error", "Некорректные данные");
            return;
        }

        saveData();
        tz1s = changeDot(QString::number(tz1));
        tzzs = changeDot(QString::number(tzz));

        window.setTextBrowser(*(new QString("Длина линии резания")));
        lengthLine();

        if (!((100*b <= (bzz+bzk)) && (100*b+1.5 >=(bzz+bzk))))
        {
            sumtz = 0;
            window.setTextBrowser(*(new QString("Длина линии резания")));
            strok = "";
            strok1 = "";
            tz.clear();
            QMessageBox::warning(this, "Error", "Выполните перерасчет, уменьшите(увеличьте) значение крайнего шага резания или первого шага резания");
            ed.set(tz1, tzz);

            ed.show();
            st = Status::Two;
            return;

        }
        else
        {
            window.setVector(&tz);
            saveDataInFile(strok);
            saveDataInFile(strok1);
            window.show();
            this->close();
        }
    }
    else{ clickTwo(tz1s, tzzs); }
}


void Corner::on_pushButton_2_clicked()
{
    changeFields();

    if(lxb == 0 || 1.15*topt < tzz)
    {
        QMessageBox::warning(this, "Error", "Некорректные данные");
        return;
    }

    try { calculateSum(); }
    catch(...) { return; }
    calculateCorner();

    doSomthing();

    window.show();
    ui->pushButton->setEnabled(true);
}

