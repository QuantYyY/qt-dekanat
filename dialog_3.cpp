#include "dialog_3.h"
#include "ui_dialog_3.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "limits.h"
#include "math.h"

Dialog_3::Dialog_3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_3)
{
    ui->setupUi(this);
}

Dialog_3::~Dialog_3()
{
    delete ui;
}

void Dialog_3::setVector(std::vector<double>* tz)
{
    this->tz = tz;
}

void Dialog_3::on_comboBox_activated(int index)
{
    if(index == 0)
        motion = ScrewStroke::PER;
    else if(index == 1)
        motion = ScrewStroke::POST;
}

void Dialog_3::createStringForSave()
{
    QString str = "Диаметр шнека; " + changeDot(QString::number(dsh)) + '\n';
    str += "Угол подъема винта шнека; " + changeDot(QString::number(alfash)) + '\n';
    str += "Диаметр ступицы шнека; " + changeDot(QString::number(ddsh)) + '\n';
    str += "Толщина винта шнека; " + changeDot(QString::number(ci)) + '\n';
    str += "Приведенная площадь потока угля; " + changeDot(QString::number(fp)) + '\n';
    str += "Коэффициент использования сечения шнека; " + changeDot(QString::number(fim)) + '\n';
    str += "Высота погрузки; " + changeDot(QString::number(hp)) + '\n';
    str += "Критическая частота вращения для шнекового исполнительного органа; " + changeDot(QString::number(nok)) + '\n';
    str += "Количество резцов в забойной линии резания; " + changeDot(QString::number(nz)) + '\n';
    str += "Количество резцов в забойной части линии резания; " + changeDot(QString::number(nnz)) + '\n';
    for (int i = 0; i < mk.size(); i++)
    {
        nnk += mk[i];
        str += "Количество резцов в линии " + QString::number(i+1) + " кутковой части равно; " + changeDot(QString::number(mk[i])) + '\n';
    }
    str += "Количество резцов в кутковой части; " + changeDot(QString::number(nnk)) + '\n';
    if (motion == ScrewStroke::POST)
        {
          for (int i = 0; i < tz->size(); i++)
          {
            buffer = round((3.6/s)*(tz->at(i) - tz1)+(360.0/nz)*(i-1));
            buffer = (int)buffer%360;
            gamma.push_back(buffer);
            str += "Центральный угол для установки резцов для линии резания " + QString::number(i+1) + "; " + changeDot(QString::number(gamma[i])) + '\n';
          }
        }
        else if (motion == ScrewStroke::PER)
        {
          for (int i = 0; i < tz->size(); i++)
          {
            buffer = round((3.6*(tz->at(i)-tz1)*((1.0/0.8)+(scp/s))/(2.0*s)+(360.0*(i-1))/nz));
            buffer = (int)buffer%360;
            gamma.push_back(buffer);
            str += "Центральный угол для установки резцов для линии резания " + QString::number(i+1) + "; " + changeDot(QString::number(gamma[i])) + '\n';
          }
        }
    saveDataInFile(str);
}

void saveFile()
{
    QFile file("file.csv");
    if(file.open(QFile::ReadWrite | QFile::Text))
    {
        QString filename = QFileDialog::getSaveFileName(
                                    NULL,
                                    "Save Document",
                                    QDir::homePath(),
                                    "Table (*.csv)");
        QFile::copy("file.csv", filename);
        file.close();
        file.remove();
    }
}

void Dialog_3::on_pushButton_clicked()
{
    hp = ui->doubleSpinBox->value();
    double di = findDouble(*(new QString("Диаметр исполнительного органа")));
    double kl = findDouble(*(new QString("Коэффициент вылета резцa")));
    double hmax = findDouble(*(new QString("Допустимая максимальная толщина стружки")));
    nz = findDouble(*(new QString("Число заходов шнека")));
    tz1 = findDouble(*(new QString("Первый шаг резания в забойной части")));
    double v = findDouble(*(new QString("Скорость подачи")));
    double no = findDouble(*(new QString("Частота вращения")));
    double b = findDouble(*(new QString("Ширина захвата")));
    double hr = findDouble(*(new QString("Мощность пласта")));
    double nlz = findDouble(*(new QString("Количество линий резания для забойной части")));
    double lpp = hmax * kl;
    scp = pow(di, (2/3));

    if(motion == ScrewStroke::POST)
    {
          s = scp;
    }
    else if (motion == ScrewStroke::PER)
    {
        s = 1.2 * scp;
    }

    dsh = di - 0.02 * lpp;
    alfash = atan(s / (PI * dsh));
    ddsh = 0.4 * sqrt(di);
    ci = 0.1 * di;
    fp = (PI*(pow(dsh,2)-pow(ddsh, 2))*(s-(ci*nz/cos(alfash))))/(4*s);
    double fo = 0.6 * fp;
    fim = 0.44*sqrt(di)*(0.9*fo/fp+0.1);
    nu = (3*v/(fo*no*sqrt(di)/fp))+(hp/(2*di));
    ho = di * nu;

    double kk1 = 1 - ((di*(lyamda-nu)/(hr*lyamda)));
    nok = b*v*(hr*kk1*lyamda-ho)/(fp*s*fim);
    if(fp != fp || kk1 != kk1 || nok != nok || nu != nu || sin(s / (PI * dsh)) == 1)
    {
        QMessageBox::warning(this, "Error", "Некорректные данные");
        return;
    }
    buffer = round(nz + 2.5);
    double buffer1 = buffer;
    mk.push_back(buffer);
    for (int i = 1; i < nz; i++)
    {
        buffer = round(buffer1 - ((buffer1-nz)*(i-1)/(nz-1)));
        mk.push_back(buffer);
    }
    nnz = nz * nlz;

    createStringForSave();
    saveFile();
    this->close();
}

