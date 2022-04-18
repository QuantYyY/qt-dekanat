#ifndef DIALOGCORNER_H
#define DIALOGCORNER_H

#include <QDialog>
#include "dialog_3.h"

enum Click{ First, Second };

namespace Ui {
class DialogCorner;
}

class DialogCorner : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCorner(QWidget *parent = nullptr);
    ~DialogCorner();

    void setTextBrowser(int, double);

    void setLengthLine(int, double);

    void setTextBrowser(QString&);

    void setVector(std::vector<double>*);
private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogCorner *ui;
    Click count = Click::First;
    Dialog_3 window;
    std::vector<double>* tz;
};

#endif // DIALOGCORNER_H
