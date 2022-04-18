#include "dialogcorner.h"
#include "ui_dialogcorner.h"
#include "mainwindow.h"



DialogCorner::DialogCorner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCorner)
{
    ui->setupUi(this);
}

void DialogCorner::setLengthLine(int ilz, double tzzbuffer)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Длина линии резания  " + QString::number(ilz) +
                               " равна " + changeDot(QString::number(tzzbuffer)) + " см\n\n");
}

void DialogCorner::setTextBrowser(int index, double betta)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Для линии резания " + QString::number(index) +
                             " угол наклона резца к направлению подачи составляет : " + changeDot(QString::number(betta)) + "\n\n");
}

void DialogCorner::setVector(std::vector<double>* tz)
{
    this->tz = tz;
}

void DialogCorner::setTextBrowser(QString& str)
{
    ui->label->setText(str);
    ui->textBrowser->setText("");
}

DialogCorner::~DialogCorner()
{
    delete ui;
}

void DialogCorner::on_pushButton_clicked()
{
    if(count == Click::Second)
    {
        window.setVector(tz);
        window.show();
    }

    if(count == Click::First)
        count = Click::Second;

    this->close();
}

