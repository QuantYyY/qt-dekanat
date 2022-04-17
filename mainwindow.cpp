#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <math.h>
#include <QErrorMessage>
#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QStringList>


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

    bool check_1 = false;
    QFile data("D:/logdata.csv");
    QTextStream file(&data);
    if (data.open(QFile::WriteOnly | QFile::Truncate |QIODevice::Append)) {
        check_1 = true;
    }

    motion = ui->textEdit->toPlainText();
    scp = pow(di,(2/3));
    if (motion == "post")
    {
      s = scp;
    }
    else if (motion == "per")
    {
      s = 1.2 * scp;
    }
    dsh = di - 0.02 * lpp;
    //std::cout << "Диаметр шнека = " << dsh << std::endl;
    file << "Диаметр шнека = " << ";"<<QString::number(dsh) <<";"<< "\n";

    double alfash;
    alfash = atan(s/(pi*dsh));
    //std::cout << "Угол подъема винта шнека = " << alfash << std::endl;
    file << "Угол подъема винта шнека = " << ";"<< QString::number(alfash) <<";"<< "\n";

    QMessageBox msgBox;
    msgBox.setWindowTitle("Рассчет условия");
    msgBox.setText("Условие выполнено!");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    d1.set(&tk2, nlk, maxsumtk, topt, sumtk, tz1, tk1, maxnlk, dsh, alfash);
    d1.set(hmax, hcp, topt);
    d1.show();

    while(d1.exec() == QDialog::Accepted){}

    std::vector<int> check;


    bool right = true;
      if ((100*b <= (bzz+bzk)) && (100*b+1.5 >=(bzz+bzk)))
      {
        msgBox.show();
        msgBox.exec();
      }
      else {
        sumtz = 0;
        while (true)
        {
          if ((100*b <= (bzz+bzk)) && (100*b+1.5 >=(bzz+bzk)))
          {
            msgBox.setWindowTitle("Рассчет условия");
            msgBox.setText("Условие выполнено!");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.show();
            msgBox.exec();
            break;
          }
          else{
            tz.clear();
            double tzi;
            msgBox.setText("Условие не выполнено\nНажмите OK и выполните перерасчет, уменьшите(увеличьте) значение крайнего шага резания или первого шага резания\n");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.show();
            int res = msgBox.exec();
            if (res == QMessageBox::Ok){
                this->d2_func();
                tz.push_back(tz1);
                tz.push_back(tzz);
                for (int ilz = 2; ilz < nlz; ilz++)
                {
                   check.push_back(ilz);
                   tzi = round((((tz1 - tk1)*(ilz - 1))/(nlz -1) + tz1)*10)/10;
                   tz.push_back(tzi);
                   sumtz += tzi;
                   //std::cout << "Длина линии резания  " << ilz << " равна " << tzi << " см" << std::endl;
                   file << "Шаг резания забойной части = " << ";"<< QString::number(tzi) << ";"<< " для линии резания " <<";"<< QString::number(ilz) <<";"<< "\n";
                   maxsumtz = sumtz;
                }

                sumtz = 0;
                bzz = maxsumtz + (round(tzz*10)/10)+tz1;
                file << "Первый шаг резания = " <<";"<< QString::number(tz1) <<";"<< "\n";
                file << "Краний шаг резания = " <<";"<< QString::number(tzz) <<";"<< "\n";
                file << "Длина забойной части исполнительного органа = " <<";"<< QString::number(bzz) <<";"<< "\n";
            } else {
                data.close();
                return;
            }
            double q1 = 100.0 * b - bzk;
            double q2 = 100.0*b + topt - bzk;
            double q3 = 100*b;
            double q4 = 100*b+1.5;
            double q5 = bzz+bzk;
            d3.set(tz, check, q1,q2,q3,q4,q5,bzz);
            check.clear();
            d3.show();
            while (d3.exec() == QDialog::Accepted){}
          //std::cout << "Необходимое условие для длины забойной части : " << 100.0 * b - bzk << " <= "<< bzz << " <= " << 100.0*b + topt - bzk << std::endl;
          //std::cout << "Проверяется условие на отклонение от ширины захвата : " << 100*b << " <= " << bzz+bzk << " <= " << 100*b+1.5 << std::endl;
          }
       }
    }
    data.close();
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

void MainWindow::d2_func(){
    d2.show();
    while (d2.exec() == QDialog::Accepted){}
    tz1 = d2.tz1;
    tzz = d2.tzz;
}

