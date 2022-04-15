#include "dialog.h"
#include "ui_dialog.h"

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

void Dialog::set(double d1, double d2, double d3)
{
    ui->label->setText(ui->label->text() + QString::number(d1));
    ui->label_2->setText(ui->label_2->text() + QString::number(d2));
    ui->label_3->setText(ui->label_3->text() + QString::number(d3));
}

void Dialog::on_pushButton_clicked()
{
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    this->close();
}



