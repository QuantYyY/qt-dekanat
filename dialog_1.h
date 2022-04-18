#ifndef DIALOG_1_H
#define DIALOG_1_H

#include <QDialog>
#include <QMessageBox>
#include "dialog_2.h"
#include "corner.h"

namespace Ui {
class Dialog_1;
}

class Dialog_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_1(QWidget *parent = nullptr);
    ~Dialog_1();

    void set(double, double, double);

private slots:
    void on_pushButton_clicked();

    void changeValueOfClass();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    QString getStringForSave();

    void calculateSumtk();

    QString getStringSumtk();

private:
    Ui::Dialog_1 *ui;
    Dialog_2 dialogWindow;
    Corner windowForCroner;
    double hcp;
    double bk;
    double e;
    double tz1;
    double tk1;
    double topt;
    double bzk;
    float sumtk = 0;
    float maxsumtk = 0;
    std::vector <double> tk2;
    int answer;
    float maxnlk = 0;
    int nlk = 2;
    double lkk;
    double sigma;
};

#endif // DIALOG_1_H
