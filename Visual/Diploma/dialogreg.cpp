#include "dialogreg.h"
#include "ui_dialogreg.h"
#include "dialoglogenter.h"
#include "ui_dialoglogenter.h"
#include "mainwindow.h"

DialogReg::DialogReg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReg)
{
    ui->setupUi(this);
}

DialogReg::~DialogReg()
{
    delete ui;
}

void DialogReg::on_pushButton_clicked()
{
    RegData rg;
    strcpy(rg.fname, ui->lineEdit->text().toStdString().c_str());
    strcpy(rg.sname, ui->lineEdit_2->text().toStdString().c_str());
    strcpy(rg.nick, ui->lineEdit_3->text().toStdString().c_str());
    strcpy(rg.hash, ui->lineEdit_4->text().toStdString().c_str());
    core1->RegLog(rg, 1);
    close();

}

void DialogReg::on_pushButton_2_clicked()
{
    close();
    exit(0);
}
