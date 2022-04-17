#ifndef DIALOG_3_H
#define DIALOG_3_H

#include <QDialog>

namespace Ui {
class Dialog_3;
}

class Dialog_3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_3(QWidget *parent = nullptr);
    ~Dialog_3();

    void set(std::vector<double> tz, std::vector<int> check, double q1, double q2, double q3, double q4, double q5, double bzz);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_3 *ui;
};

#endif // DIALOG_3_H
