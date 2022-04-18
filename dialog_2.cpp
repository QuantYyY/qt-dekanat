#include "dialog_2.h"
#include "ui_dialog_2.h"
#include "dialog.h"
#include "mainwindow.h"

Dialog_2::Dialog_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_2)
{
    ui->setupUi(this);
}

void Dialog_2::setSumtk(double sumtk)
{
    ui->textBrowser->setText(ui->textBrowser->toPlainText() + "sumtk = " + changeDot(QString::number(sumtk)) + '\n');
}

void Dialog_2::setMaxSumtk(double maxsumtk, double topt)
{
    ui->label->setText("Необходимое условие для длины кутковой части :\n" + changeDot(QString::number(1.3*topt)) + " <= " +
                       changeDot(QString::number(maxsumtk)) + " <= " + changeDot(QString::number(2*topt)));
}

Dialog_2::~Dialog_2()
{
    delete ui;
}

void Dialog_2::on_pushButton_clicked()
{
    this->close();
}

