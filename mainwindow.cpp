#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <math.h>
#include <QErrorMessage>
#include <QDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //b = ui->doubleSpinBox->value();
    hr = ui->doubleSpinBox_2->value();
    y = ui->doubleSpinBox_3->value();
    v = ui->doubleSpinBox_4->value();
    di = ui->doubleSpinBox_5->value();
    no = ui->doubleSpinBox_6->value();
    nz = ui->doubleSpinBox_7->value();
    lkk = ui->doubleSpinBox_9->value();
    sigma = ui->doubleSpinBox_10->value() * pi / 180;
    kl = ui->doubleSpinBox_11->value();

    lpp = lkk * sin(sigma);
    hmax = lpp / kl;

    hcp = 2.0*hmax / pi;

    bk = ui->doubleSpinBox_14->value();
    e = ui->doubleSpinBox_15->value();

    topt = ((5.0*hcp)/(0.5*hcp+4.5)+0.7*hcp)*((1.47*e)/(e+1.2))+bk;

    tk1 = ui->doubleSpinBox_16->value();
    tz1 = ui->doubleSpinBox_17->value();

    if(tk1 > 0.45*topt)
    {
        ui->label_1->setText("Введён не корректный крайний кутковый шаг резания");
        return;
    }else{
        ui->label_1->setText("");
    }

    if(tz1 > 0.85*topt)
    {
        ui->label_1->setText("Введён не корректный первый шаг резания в забойной части");
        return;
    }else{
        ui->label_1->setText("");
    }

    d1.set(&tk2, nlk, maxsumtk, topt, sumtk, tz1, tk1, maxnlk);
    d1.set(hmax, hcp, topt);
    d1.show();
}



void MainWindow::on_pushButton_2_clicked()
{
    b = ui->doubleSpinBox->value();
    hr = ui->doubleSpinBox_2->value();
    y = ui->doubleSpinBox_3->value();
    v = ui->doubleSpinBox_4->value();
    di = ui->doubleSpinBox_5->value();
    no = ui->doubleSpinBox_6->value();
    nz = ui->doubleSpinBox_7->value();
    lkk = ui->doubleSpinBox_9->value();
    sigma = ui->doubleSpinBox_10->value() * pi / 180;
    kl = ui->doubleSpinBox_11->value();

    lpp = lkk * sin(sigma);
    hmax = lpp / kl;

    hcp = 2.0*hmax / pi;

    bk = ui->doubleSpinBox_14->value();
    e = ui->doubleSpinBox_15->value();

    topt = ((5.0*hcp)/(0.5*hcp+4.5)+0.7*hcp)*((1.47*e)/(e+1.2))+bk;

    ui->label_12->setText("0,45 tопт = " + QString::number(0.45*topt));
    ui->label_18->setText("0,85 tопт = " + QString::number(0.85*topt));
}

