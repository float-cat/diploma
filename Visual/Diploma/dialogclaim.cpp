#include "dialogclaim.h"
#include "ui_dialogclaim.h"
#include "dialoggame.h"

DialogClaim::DialogClaim(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClaim)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(GameShow()));
}

DialogClaim::~DialogClaim()
{
    delete ui;
}

void DialogClaim::on_pushButton_clicked()
{
    close();
}

void DialogClaim::GameShow()
{
    DialogGame *dg = new DialogGame(this);
    dg->open();
}

void DialogClaim::on_pushButton_2_clicked()
{
    close();
}
