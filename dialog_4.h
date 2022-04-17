#ifndef DIALOG_4_H
#define DIALOG_4_H

#include <QDialog>

namespace Ui {
class Dialog_4;
}

class Dialog_4 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_4(QWidget *parent = nullptr);
    ~Dialog_4();

    void set(double hp);
    void set(std::vector<double>* tk2, int nlk, float maxsumtk, float topt, float sumtk,
             double tz1, float tk1, float maxnlk, double dsh, double alfash, double ddsh,
             double ci, double fp, double fo, double nu, double hp, double nok, double kk1,
             double v, double no, double di, double lyamda, double hr, double ho, double s,
             double fim, double b, double nz, double nlz, QString motion, std::vector<double>* tz, double scp);

private slots:
    void on_pushButton_1_clicked();

private:
    Ui::Dialog_4 *ui;
};

#endif // DIALOG_4_H
