#include "dialog_2.h"
#include "ui_dialog_2.h"

Dialog_2::Dialog_2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_2)
{
    ui->setupUi(this);
}

Dialog_2::~Dialog_2()
{
    delete ui;
}

void Dialog_2::on_pushButton_clicked()
{
    tz1 = ui->doubleSpinBox->value();
    tzz = ui->doubleSpinBox_2->value();
    this->close();
}

