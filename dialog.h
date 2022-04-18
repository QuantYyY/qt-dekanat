#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include "dialog_1.h"

QString changeDot(QString);

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    QString getStringForSave();

private:
    Ui::Dialog *ui;
    double hmax = NAN;
    Dialog_1 window;
};

#endif // DIALOG_H
