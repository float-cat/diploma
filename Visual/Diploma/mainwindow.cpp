/* NEED */
#include <QApplication>
#include <QDialog>
#include "mainwindow.h"
#include "dialogcreategame.h"
#include "dialogjoin.h" //bad including! why here??
#include "dialoglogenter.h"
#include "dialogreg.h"
#include "ui_mainwindow.h"
#include <QTextBrowser>
#include <QMessageBox>

#include "ui_dialogreg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    MsgAboutProgram = new QMessageBox(tr("О программе"), tr("Здесь будет информация о программе \nЭто следующая строка \n"), QMessageBox::Information, 0, 0, 0, 0, 0);
    localprev = NULL;
    localmodes = NULL;
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(CreateGameShow()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(DownloadShow()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(JoinShow()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(ConnectToServer()));
}

MainWindow::~MainWindow()
{
    delete MsgAboutProgram;
    delete ui;
}

char *MainWindow::GetNick()
{
    return NULL;
}

void MainWindow::AskerDoor(int cmd, void *data)
{
    ModeData *p;
    cout << "cmd in askerdoor: " << cmd << endl;
    switch(cmd){
        case API_GAMELISTITEM:
            dj->AddToList(*(GameData*)data);
            break;
        case API_MODELISTITEM:
            mw->AddToList(*(ModeData*)data);
            break;
        case API_MODEDOWNLOAD:
            mw->FinishDownload();
            break;
    }
}

void MainWindow::AddToList(ModeData modedata){
    if(isInlist(modedata)) return;
    ui->listWidget_2->addItem(modedata.title);
    if(root==NULL)
        prev = root = new ModeDataItem;
    else
        prev = prev->next = new ModeDataItem;
    prev->data = modedata;
    prev->next = NULL;
}

void MainWindow::AddToLocalList(ModeData modedata){
    ui->listWidget->addItem(modedata.title);
    if(localmodes==NULL)
        localprev = localmodes = new ModeDataItem;
    else
        localprev = localprev->next = new ModeDataItem;
    localprev->data = modedata;
    localprev->next = NULL;
}

void MainWindow::StartDownload(){
    ui->listWidget->setEnabled(false);
    ui->listWidget_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void MainWindow::FinishDownload(){
    ui->listWidget->setEnabled(true);
    ui->listWidget_2->setEnabled(true);
}

bool MainWindow::isInlist(ModeData modedata){
    ModeDataItem *p = localmodes;
    while(p!=NULL){
        if(strcmp(p->data.fname, modedata.fname)==0) return true;
        p = p->next;
    }
    return false;
}

char *MainWindow::GetSelectedMode(void){
    ModeDataItem *p = localmodes;
    int number = ui->listWidget->currentRow();
    while(p!=NULL && number-->0)
        p = p->next;
    if(p==NULL) return NULL;
    return p->data.fname;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::CreateGameShow()
{
    DialogCreateGame *f = new DialogCreateGame(this); // Bad affect! No release memory!
    f->setWindowTitle(ui->listWidget->currentItem()->text());
    f->open();
}

void MainWindow::DownloadShow() // hide in core!!!!
{
    /*DialogDownload *dd = new DialogDownload(this);
    dd->setWindowTitle(ui->listWidget_2->currentItem()->text());
    dd->open();*/
    FILE *tmpf;
    ModeDataItem *p = root;
    int number = ui->listWidget_2->currentRow();
    while(p!=NULL && number-->0)
        p = p->next;
    if(p==NULL) return;
    if(isInlist(p->data)) return;
    StartDownload();
    tmpf = fopen("modes/modelist", "at");
    fprintf(tmpf, "%s=%s\n", p->data.fname, p->data.title);
    fclose(tmpf);
    AddToLocalList(p->data);
    core1->GetMode(p->data.fname);
}

void MainWindow::JoinShow()
{
    //if(!OnServerExistSelectMode) return;
    dj->setWindowTitle(ui->listWidget->currentItem()->text());
    dj->ClearGameList();
    //core1->GetGameList(GetFromLocalList(ui->listWidget->currentItem()->text().toStdString().c_str()).fname);
    core1->GetGameList("test");
    dj->open();
}

void MainWindow::ConnectToServer(){
    FILE *pf; int i;
    char readbuf[128], *second;
    ModeDataItem *p;
    root = prev = NULL;
    core1->Init(INIT_ASKER);
    pf = fopen("modes/modelist", "rt"); // v class?
    readbuf[0]=0;
    while(!feof(pf)){
        fgets(readbuf, 128, pf);
        if(strlen(readbuf)>0) readbuf[strlen(readbuf)-1] = 0; // 1 in Windows?
        if(strlen(readbuf)==0) break;
        for(i=0; i<strlen(readbuf); i++)
            if(readbuf[i] == '='){
                readbuf[i]=0;
                second = &readbuf[i+1];
            }
        p = localmodes;
        localmodes = new ModeDataItem;
        if(localprev == NULL) localprev = localmodes;
        strcpy(localmodes->data.fname, readbuf);
        strcpy(localmodes->data.title, second);
        localmodes->next = p;
        readbuf[0] = 0;
        ui->listWidget->addItem(second);
    }
    fclose(pf);
    core1->GetModeList();
}

/*void MainWindow::Qslot(QString s)
{
    ui->label_2->setText(s);
}*/

void MainWindow::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    if(item->isSelected()) ui->pushButton_3->setEnabled(true);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(item->isSelected()) ui->pushButton->setEnabled(true);
    if(item->isSelected()) ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_action_triggered()
{
    exit(0);
}

void MainWindow::on_action_2_triggered()
{
    QTextBrowser* b=new QTextBrowser; // Remove menu item!

    b->resize(500,300);
      b->setWindowTitle(tr("Справка"));
      b->show();
      b->setHtml(tr(
                     "* <b>Раздел I:</b> Использование клиента.<br/>"
                     "* <b>Раздел II:</b> Программирование игры.<br/>"
                     ));
}

void MainWindow::on_action_4_triggered()
{
    MsgAboutProgram->show();
}

void MainWindow::on_pushButton_2_clicked()
{

}
