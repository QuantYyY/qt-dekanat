#include "dialog_3.h"
#include "ui_dialog_3.h"

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

void Dialog_3::set(std::vector<double> tz, std::vector<int> check, double q1, double q2, double q3, double q4, double q5, double bzz){
    for (int i = 0; i < check.size();i++){
        ui->textBrowser->setText(ui->textBrowser->toPlainText() + "Длина линии резания  " + QString::number(check[i]) + " равна " +QString::number(tz[i+2])+ " см" + "\n");
    }

    ui->label->setText("Необходимое условие для длины забойной части : " +QString::number(q1)+ " <= " + QString::number(bzz) + " <= " +QString::number(q2));
    ui->label_2->setText("Проверяется условие на отклонение от ширины захвата : " +QString::number(q3)+ " <= " +QString::number(q5)+ " <= " +QString::number(q4));
}

void Dialog_3::on_pushButton_clicked()
{
    this->close();
}

