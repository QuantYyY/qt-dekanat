#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_1.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    double b = 0;
    double di;
    double hr;
    double y;
    double v;
    double hmax;
    double kl;
    double lpp;
    double lkk;
    double sigma;
    double hcp;
    const double pi = 3.141592653589793;
    float topt;
    double bk;
    double e;
    float tk1;
    double no;
    double nz;
    double tz1;
    double bzk;
    float sumtk = 0;
    float maxsumtk = 0;
    std::vector <double> tk2;
    int answer;
    float maxnlk = 0;
    int nlk = 2;
    Dialog_1 d1;
    double lxb;
    double sum = 0;
    std::vector <double> betta;
};
#endif // MAINWINDOW_H
