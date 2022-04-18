#include "dialog_1.h"
#include "ui_dialog_1.h"
#include "dialog.h"
#include "mainwindow.h"

Dialog_1::Dialog_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_1)
{
    ui->setupUi(this);
}

Dialog_1::~Dialog_1()
{
    delete ui;
}

void Dialog_1::set(double hcp, double lkk, double sigma)
{
    this->hcp = hcp;
    this->lkk = lkk;
    this->sigma = sigma;
}

QString Dialog_1::getStringForSave()
{
    QString string = "Конструктивная ширина режущей части забойного резца; " + ui->doubleSpinBox->text() + '\n';
    string += "Показатель степени хрупкости; " + ui->doubleSpinBox_2->text() + '\n';
    string += "Крайний кутковый шаг резания; " + ui->doubleSpinBox_3->text() + '\n';
    string += "Первый шаг резания в забойной части; " + ui->doubleSpinBox_4->text() + '\n';
    string += "Средняя оптимальная ширина стружки для забойных резцов; " + changeDot(QString::number(topt)) + '\n';
    return string;
}

void Dialog_1::changeValueOfClass()
{
    bk = ui->doubleSpinBox->value();
    e = ui->doubleSpinBox_2->value();
    tk1 = ui->doubleSpinBox_3->value();
    tz1 = ui->doubleSpinBox_4->value();
}

void Dialog_1::calculateSumtk()
{
    changeValueOfClass();
    if(0.45*topt < tk1 || 0.85*topt < tz1)
    {
        QMessageBox::warning(this, "Error", "Некорректные данные");
        throw 1;
    }

    QString str;
    if(maxsumtk == 0)
    {
        do{
            for (int ilk = 1; ilk <= nlk; ilk++)
            {
              float tkbuffer = (((tz1 - tk1)*(ilk - 1))/(nlk -1)) + tk1;
              tk2.push_back(tkbuffer);
              sumtk += tkbuffer;
              dialogWindow.setSumtk(sumtk);
            }
            if (sumtk > maxsumtk && (sumtk >= 1.3*topt) && (sumtk <= 2*topt))
            {
              maxsumtk = sumtk;
              maxnlk = nlk;
              dialogWindow.setMaxSumtk(maxsumtk, topt);
              break;
            }
            else {
              tk2.clear();
              sumtk = 0;
              nlk++;
            }
        }while(true);
    }
}

void Dialog_1::on_pushButton_clicked()
{
    try { calculateSumtk(); }
    catch(...){ return; }
    dialogWindow.show();
}

QString Dialog_1::getStringSumtk()
{
    QString string;
    for (int i = 0; i < tk2.size(); i++)
    {
        string += "Шаг резания кутковой части для линии резания " + QString::number(i+1) + "; " + changeDot(QString::number(tk2[i])) + '\n';
    }

    string += "Необходимое условие для длины кутковой части; " + changeDot(QString::number(1.3*topt)) + " <= " +
            changeDot(QString::number(maxsumtk)) + " <= " + changeDot(QString::number(2*topt)) + '\n';

    return string;
}

void Dialog_1::on_pushButton_3_clicked()
{
    changeValueOfClass();

    topt = ((5.0*hcp)/(0.5*hcp+4.5)+0.7*hcp)*((1.47*e)/(e+1.2))+bk;
    ui->label_7->setText(changeDot(QString::number(topt)));

    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(true);
}

void Dialog_1::on_pushButton_2_clicked()
{
    try{ calculateSumtk(); }
    catch(...){ return; }

    QString str = getStringForSave() + getStringSumtk();

    saveDataInFile(str);
    windowForCroner.setFields(maxsumtk, tk2, lkk, sigma);
    windowForCroner.show();
    this->close();
}
