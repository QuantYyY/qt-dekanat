#ifndef DIALOG_1_H
#define DIALOG_1_H

#include <QDialog>

namespace Ui {
class Dialog_1;
}

class Dialog_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_1(QWidget *parent = nullptr);
    ~Dialog_1();

    void set(double d1, double d2, double d3);

    void set(std::vector<double>* tk2, int nlk, double maxsumtk, double topt, double sumtk, double tz1, double tk1,  float maxnlk);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_1 *ui;
};

#endif // DIALOG_1_H
