#ifndef DIALOG_2_H
#define DIALOG_2_H

#include <QDialog>

namespace Ui {
class Dialog_2;
}

class Dialog_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_2(QWidget *parent = nullptr);
    ~Dialog_2();

private slots:
    void on_pushButton_clicked();

public:
    double tz1;
    double tzz;

private:
    Ui::Dialog_2 *ui;

};

#endif // DIALOG_2_H
