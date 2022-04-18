#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

void ErrorDialog::set(double& tz, double& tzzz)
{
    ui->doubleSpinBox->setValue(tz);
    ui->doubleSpinBox_2->setValue(tzzz);
    tz1 = &tz;
    tzz = &tzzz;
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::on_pushButton_clicked()
{
    *tz1 = ui->doubleSpinBox->value();
    *tzz = ui->doubleSpinBox_2->value();
    this->close();
    st = StatusWrite::Write;
}

