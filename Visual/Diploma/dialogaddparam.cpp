#include "dialogaddparam.h"
#include "ui_dialogaddparam.h"

DialogAddParam::DialogAddParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddParam)
{
    ui->setupUi(this);
}

DialogAddParam::~DialogAddParam()
{
    delete ui;
}

void DialogAddParam::on_pushButton_clicked()
{
    close();
}
