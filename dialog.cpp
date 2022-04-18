#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"

QString changeDot(QString str)
{
    if(str.indexOf('.') > 0)
    {
        str[str.indexOf('.')] = ',';
    }
    return str;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getStringForSave()
{
    QString string = "Конструктивный вылет забойного резца; " + ui->doubleSpinBox->text() + '\n';
    string += "Угол установки забойного резца к поверхности резания; " + ui->doubleSpinBox_2->text() + '\n';
    string += "Коэффициент вылета резцa; " + ui->doubleSpinBox_3->text() + '\n';
    string += "Допустимая максимальная толщина стружки; " + changeDot(QString::number(hmax)) + '\n';
    string += "Средняя толщина стружки; " + changeDot(QString::number(2.0 * hmax / PI)) + '\n';
    return string;
}

void Dialog::on_pushButton_clicked()
{
    double lkk = ui->doubleSpinBox->value();
    double sigma = ui->doubleSpinBox_2->value();
    double kl = ui->doubleSpinBox_3->value();

    sigma *= PI/180;
    double lpp = lkk * sin(sigma);
    hmax = lpp / kl;
    double hcp = 2.0 * hmax / PI;
    window.set(hcp, lkk, sigma);

    QString string = getStringForSave();

    if(string.indexOf(" 0,00000\n") > 0 || hmax != hmax)
    {
        QMessageBox::warning(this, "Error", "Некорректные данные");
        return;
    }

    if(ui->label_5->text()[ui->label_5->text().length() - 1] == ' ')
    {
        ui->label_5->setText(ui->label_5->text() + changeDot(QString::number(hmax)));
    }

    if(ui->label_6->text()[ui->label_6->text().length() - 2] == '=')
    {
        ui->pushButton_3->setEnabled(true);
        ui->label_6->setText(ui->label_6->text() + changeDot(QString::number(hcp)));
    }
    saveDataInFile(string);
}

void Dialog::on_pushButton_3_clicked()
{
    window.show();
    this->close();
}

