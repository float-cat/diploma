#include "dialogjoin.h"
#include "dialoggame.h"
#include "dialogclaim.h"
#include "ui_dialogjoin.h"

DialogJoin::DialogJoin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogJoin)
{
    ui->setupUi(this);
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(Claim()));
    root = NULL;
}

DialogJoin::~DialogJoin()
{
    delete ui;
}

void DialogJoin::ClearGameList(void){
    GameDataItem *p;
    ui->listWidget->clear();
    while(root!=NULL){
        p = root->next;
        delete root;
        root = p;
    }
}

void DialogJoin::AddToList(GameData gamedata){
    ui->listWidget->addItem(gamedata.title);
    if(root==NULL)
        prev = root = new GameDataItem;
    else
        prev = prev->next = new GameDataItem;
    prev->data = gamedata;
    prev->idx = -1;
    prev->next = NULL;
}

void DialogJoin::on_pushButton_2_clicked()
{
    close();
}

void DialogJoin::on_pushButton_3_clicked()
{
}

void DialogJoin::Claim()
{
    //DialogClaim *c = new DialogClaim(this);
    //c->setWindowTitle(ui->listWidget->currentItem()->text());
    //c->open();
    GameDataItem *p = root;
    int number = ui->listWidget->currentRow();
    while(p!=NULL && number-->0)
        p = p->next;
    if(p==NULL) return;
    printf("%d\n", p->data.port);
    core1->Port(p->data.port);
    core1->SetPlayerNick(globalnick);
    core1->Init(INIT_GAMEPROC, p->data.mode);
    dg->setWindowTitle(p->data.title);
    dg->show();
}

void DialogJoin::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(item->isSelected()) ui->pushButton_3->setEnabled(true);
}
