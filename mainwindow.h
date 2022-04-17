#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_1.h"
#include <vector>
#include "dialog_2.h"
#include "dialog_3.h"

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

    void d2_func();

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
    double tzz;
    double bzk;
    double nlz = 10;
    double maxsumtz;
    float sumtk = 0;
    float sumtz;
    float maxsumtk = 0;
    std::vector <double> tk2;
    int answer;
    float maxnlk = 0;
    int nlk = 2;
    Dialog_1 d1;
    Dialog_2 d2;
    double lxb;
    double sum = 0;
    std::vector <double> betta;
    float bzz = 1.0;
    std::vector<double> tz;
    Dialog_3 d3;

    double k1;
        const double lyamda = 1.6;
        double ho;
        double fp;
        double s;
        double scp;
        double fim;
        double dsh;
        QString motion;
};
#endif // MAINWINDOW_H
