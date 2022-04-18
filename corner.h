#ifndef CORNER_H
#define CORNER_H

#include <QDialog>
#include "dialogcorner.h"
#include "errordialog.h"

enum Status{ One, Two };

namespace Ui {
class Corner;
}

class Corner : public QDialog
{
    Q_OBJECT

public:
    explicit Corner(QWidget *parent = nullptr);
    ~Corner();

    void setFields(double, std::vector<double>, double, double);
private slots:
    void on_pushButton_clicked();

    void calculateSum();

    void calculateCorner();

    void lengthLine();

    void doSomthing();

    void on_pushButton_2_clicked();

    void changeFields();

    void saveData();

    void clickTwo(QString&, QString&);
private:
    Ui::Corner *ui;
    std::vector <double> betta;
    DialogCorner window;
    double maxsumtk;
    double sum = 0;
    std::vector<double> tk2;
    double lkk;
    double bzk;
    double lxb;
    double sigma;
    int nlz = 0;
    float sumtz = 0;
    float maxsumtz = 0;
    double tz1 = 0;
    double topt = 0;
    double tk1 = 0;
    double tzz;
    std::vector <double> tz;
    ErrorDialog ed;
    double b;
    double bzz;
    QString strok;
    QString strok1;
    Status st = Status::One;
    QString tz1s;
    QString tzzs;
};

#endif // CORNER_H
