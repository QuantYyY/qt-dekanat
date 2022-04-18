#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>

enum StatusWrite
{
    Write, NotWrite
};

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = nullptr);
    ~ErrorDialog();

    void set(double&, double&);

    StatusWrite st = StatusWrite::NotWrite;
private slots:
    void on_pushButton_clicked();

private:
    Ui::ErrorDialog *ui;
    double *tz1;
    double *tzz;
};

#endif // ERRORDIALOG_H
