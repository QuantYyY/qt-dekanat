#ifndef DIALOG_3_H
#define DIALOG_3_H

#include <QDialog>

enum ScrewStroke{ POST, PER };

namespace Ui {
class Dialog_3;
}

class Dialog_3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_3(QWidget *parent = nullptr);
    ~Dialog_3();

    void setVector(std::vector<double>*);
private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void createStringForSave();

private:
    Ui::Dialog_3 *ui;
    ScrewStroke motion;
    std::vector <double> mk;
    double k1;
    const double lyamda = 1.6;
    double ho;
    double fp;
    double s;
    double scp;
    double fim;
    double dsh;
    double alfash;
    double ddsh;
    double ci;
    double nu;
    double nok;
    double hp;
    double nnz;
    double nnk = 0;
    double nz;
    std::vector <double> gamma;
    std::vector<double>* tz;
    double buffer;
    double tz1;
};

#endif // DIALOG_3_H
