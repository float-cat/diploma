#include "dialogcreategame.h"
#include "ui_dialogcreategame.h"
#include "mainwindow.h"
#include "dialogaddparam.h"
#include "dialogjoin.h"

DialogCreateGame::DialogCreateGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateGame)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(GameShow1()));
}

DialogCreateGame::~DialogCreateGame()
{
    delete ui;
}

void DialogCreateGame::AddParamShow()
{
    DialogAddParam *dap = new DialogAddParam(this);
    dap->open();
}

void DialogCreateGame::on_pushButton_2_clicked()
{
    close();
}

void DialogCreateGame::on_pushButton_3_clicked()
{
    close();
}

void DialogCreateGame::GameShow1()
{
    GameData gamedata;
    strcpy(gamedata.title, ui->lineEdit->text().toStdString().c_str());
    strcpy(gamedata.mode, mw->GetSelectedMode());
    core1->SetPlayerNick(globalnick);
    core1->Init(INIT_GAMEPROC, gamedata.mode);
    dg->setWindowTitle(ui->lineEdit->text());
    dg->open();
    gamedata.port = core1->ClientInPort();
    gamedata.ip = -1; // AUTO DETECT
    core1->RegisterGame(gamedata);
}
