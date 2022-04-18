#include "mainwindow.h"
#include "./ui_mainwindow.h"

void saveDataInFile(QString& str)
{
    QFile file("file.csv");
    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QTextStream stream(&file);
        stream << str;
        file.close();
    }
}

double findDouble(QString& findStr)
{
    QString str = "";
    QFile file("file.csv");
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QString string = file.readAll();
        for(int i = string.indexOf(findStr); string[i] != '\n'; i++)
        {
            if(string[i] >= '0' && string[i] <= '9')
                str += string[i];
            else if(string[i] == ',')
                str += '.';
        }
        file.close();
    }
    return str.toDouble();
}


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
    QFile file("file.csv");
    if(file.open(QFile::WriteOnly | QFile::Text))
    {
        file.resize(0);
        file.close();
    }

    QString strSave = "Ширина захвата; " + ui->doubleSpinBox->text() + '\n';
    strSave += "Мощность пласта; " + ui->doubleSpinBox_2->text() + '\n';
    strSave += "Плотность угля; " + ui->doubleSpinBox_3->text() + '\n';
    strSave += "Скорость подачи; " + ui->doubleSpinBox_4->text() + '\n';
    strSave += "Диаметр исполнительного органа; " + ui->doubleSpinBox_5->text() + '\n';
    strSave += "Частота вращения; " + ui->doubleSpinBox_6->text() + '\n';
    strSave += "Число заходов шнека; " + ui->doubleSpinBox_7->text() + '\n';

    if(strSave.indexOf(" 0,00000\n") > 0)
    {
        QMessageBox::warning(this, "Error", "Некорректные данные");
        return;
    }

    saveDataInFile(strSave);

    window.show();
    this->close();
}

