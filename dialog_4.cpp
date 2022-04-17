#include "dialog_4.h"
#include "ui_dialog_4.h"



Dialog_4::Dialog_4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_4)
{
    ui->setupUi(this);
}

Dialog_4::~Dialog_4()
{
    delete ui;
}


void Dialog_4::set(std::vector<double>* tk2, int nlk, float maxsumtk, float topt, float sumtk,
                   double tz1, float tk1, float maxnlk, double dsh, double alfash, double ddsh,
                   double ci, double fp, double fo, double nu, double hp, double nok, double kk1,
                   double v, double no, double di, double lyamda, double hr, double ho, double s,
                   double fim, double b, double nz, double nlz, QString motion, std::vector<double>* tz, double scp)
{

    //file << "Высота погрузки = " << hp << ";" << "\n";

    ui->label->setText("Высота погрузки =" + QString::number(hp));
    nu = (3 * v / (fo * no * sqrt(di) / fp)) + (hp / (2 * di));

    kk1 = 1 - ((di * (lyamda - nu) / (hr * lyamda)));
    nok = b * v * (hr * kk1 * lyamda - ho) / (fp * s * fim);

    ui->label_2->setText("Критическая частота вращения для шнекового исполнительного органа =" + QString::number(nok));
    //file << "Критическая частота вращения для шнекового исполнительного органа = " << nok << ";" << "\n";
    //file << "Количество резцов в забойной линии резания = " << nz << ";" << "\n";

    std::vector <double> mk;
        double buffer;
        buffer = round(nz + 2.5);
        double buffer1 = buffer;
        mk.push_back(buffer);
        for (int i = 1; i < nz; i++)
        {
            buffer = round(buffer1 - ((buffer1 - nz) * (i - 1) / (nz - 1)));
            mk.push_back(buffer);
        }

    double nnz;
        nnz = nz * nlz;

    ui->label_3->setText("Количество резцов в забойной части исполнительного органа =" + QString::number(nnz));
    //std::cout << "Количество резцов в забойной части исполнительного органа = " << nnz << std::endl;
    //file << "Количество резцов в забойной части линии резания = " << nnz << ";" << "\n";

    double nnk = 0;
        for (int i = 0; i < mk.size(); i++)
            {
                nnk += mk[i];
                //file << "Количество резцов в линии " << i + 1 << " кутковой части равно " << mk[i] << ";" << "\n";;
            }
        //std::cout << "Количество резцов в кутковой части исполнительного органа = " << nnk << ";" << "\n";
        ui->label_4->setText("Количество резцов в кутковой части исполнительного органа =" + QString::number(nnk));

        //file << "Количество резцов в кутковой части = " << nnk << ";" << "\n";



        std::vector <double> gamma;
            if (motion == "post")
            {
                for (int i = 0; i < tz->size(); i++)
                {
                    ui->label_5->setText("Ход винта = " + motion);
                    buffer = round((3.6 / s) * ((*tz)[i] - tz1) + (360.0 / nz) * (i - 1));
                    buffer = (int)buffer % 360;
                    gamma.push_back(buffer);
                    ui->textBrowser->setText("Центральный угол для установки резцов = " + QString::number(gamma[i]) + "  для линии резания " + QString::number(i+1) + "\n");

                    //ui->textBrowser->setText(ui->textBrowser->toPlainText() + "sumtk = " + QString::number(sumtk) + "\n");
                    //file << "Центральный угол для установки резцов = " << gamma[i] << " для линии резания " << i + 1 << ";" << "\n";

                }
            }

            else if (motion == "per")
            {
                for (int i = 0; i < tz->size(); i++)
                {
                    ui->label_5->setText("Ход винта = " + motion);
                    buffer = round((3.6 * ((*tz)[i] - tz1) * ((1.0 / 0.8) + (scp / s)) / (2.0 * s) + (360.0 * (i - 1)) / nz));
                    buffer = (int)buffer % 360;
                    gamma.push_back(buffer);
                    ui->textBrowser->setText("Центральный угол для установки резцов = " + QString::number(gamma[i]) + "  для линии резания " + QString::number(i+1) + "\n");

                    //std::cout << "Центральный угол для установки резцов = " << gamma[i] << " для линии резания " << i + 1 << std::endl;
                    //file << "Центральный угол для установки резцов = " << gamma[i] << " для линии резания " << i + 1 << ";" << "\n";

                }
            }






}



void Dialog_4::on_pushButton_1_clicked()
{

    this->close();
}

