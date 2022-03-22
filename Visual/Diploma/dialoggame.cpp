#include "dialoggame.h"
#include "ui_dialoggame.h"

// kakie mozhno perenesti v not static?
Ui::DialogGame *DialogGame::tmp = 0;
QCards **DialogGame::Players = NULL;
QPushButton **DialogGame::ctrlbuttons = NULL;
QCards **DialogGame::cardsgroups = NULL;
extern DialogGame *dg;

DialogGame::DialogGame(QWidget *parent, char *nick) :
    QDialog(parent),
    ui(new Ui::DialogGame)
{
    tmp = ui;
    ui->setupUi(this);
    problems = prevprob = NULL;
    playerscount = 0;
    nil = &playerscount;
    //
    QCards::initCollectObj(this);
    //
    //
    if(ctrlbuttons == NULL){
        ctrlbuttons = new QPushButton*[10];
        for(int i=0; i<10; i++)
            ctrlbuttons[i] = NULL;
    }
    if(cardsgroups == NULL){
        cardsgroups = new QCards*[20];
        for(int i=0; i<20; i++)
            cardsgroups[i] = NULL;
    }
    //
    ui->pushButton->setEnabled(true);
    tmp->listWidget->insertItem(0,/*mw->GetNick()*/nick);
    tmp->listWidget->item(0)->setCheckState(Qt::Unchecked);

    unsigned short in_port, con_port;
    /*core1 = new CoreZombie(BackDoor);
    in_port = core1->ClientInPort();*/
    /*//Test -- on
int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(::connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }

    send(sock, &in_port, sizeof(unsigned short), 0);
    recv(sock, &con_port, sizeof(unsigned short), 0);

    ::close(sock);
    //Test -- off*/

    /*core1->SetPlayerNick(nick); //zdes' lychshe dannie
    if(con_port > 0)
        core1->Port(con_port);
    core1->Init(INIT_GAMEPROC);*/


    //ui->listWidget->item(ui->listWidget->count())->setCheckState(Qt::Unchecked);

    ui->pushButton_3->focusWidget();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCards()));
    timer->start(1000);
}

DialogGame::~DialogGame()
{
    int i;
    delete timer;
    for(i=0; i<playerscount; i++)
        delete Players[i];
    delete [] Players;
    delete ui;
    QCards::releaseCollectObj();
}

void DialogGame::BackDoor(int code, void * data){
    printf("HERE!!! 3 [%d == %d]", code, API_CREATEBUTTON); fflush(stdout);
    int i; int size, cgid; char *ptr; int *mja;
    int *retsize, *retval;
    switch(code){
        case API_NEWPLAYER:
            tmp->listWidget->insertItem(tmp->listWidget->count(),(char*)data);
            tmp->listWidget->item(tmp->listWidget->count()-1)->setCheckState(Qt::Unchecked);
            break;
        case API_NEWCHATLINE:
            tmp->textBrowser->append((char*)data);
            break;
        case API_READYCHECK:
            tmp->listWidget->item((*(int*)data)+1)->setCheckState(Qt::Checked);
            dg->isAllReady();
            break;
        case API_ADDCARDSONHAND: case API_ADDTOPLAYERCARDS:
            Players[0]->LaterRun(QCARDS_CTRL_ADD, *(int*)(((void **)data)[0]), (int*)(((void **)data)[1]));
            break;
        case API_ADDSECRETCARDSONHAND:
            Players[*(int*)(((void **)data)[0])+1]->LaterRun(QCARDS_CTRL_SADD, *(int*)(((void **)data)[1]), NULL);
            break;
        case API_OPENCARDSONHAND:
            Players[*(int*)(((void **)data)[0])+1]->LaterRun(QCARDS_CTRL_OPEN, *(int*)(((void **)data)[1]), (int*)(((void **)data)[2]));
            break;
        case API_CREATEBUTTON:
cout << "  --> 1 " << endl; fflush(stdout);
            for(i=0; i<10 && ctrlbuttons[i] != NULL; i++) {cout << "  --> 2 [" << i << "]" << endl; fflush(stdout);};
            if(i<10) {
cout << "  --> 3 " << endl; fflush(stdout);
                ctrlbuttons[i] = (QPushButton *)dg->nil;
cout << "  --> 4 " << endl; fflush(stdout);
                int *button_id;
cout << "  --> 5 " << endl; fflush(stdout);
                ptr = (char*)data+(sizeof(int)+sizeof(int*));
cout << "  --> 6 " << endl; fflush(stdout);
                memcpy(&size, data, sizeof(int));
cout << "  --> 7 " << endl; fflush(stdout);
                memcpy(&button_id, (char*)data+sizeof(int), sizeof(int*));
cout << "  --> sizeof int " << sizeof(int) << endl; fflush(stdout);
cout << "  --> 8 " << endl; fflush(stdout);
                *button_id = i;
cout << "  --> 9 " << endl; fflush(stdout);
                memcpy(ptr+(size-sizeof(int*)), &i, sizeof(int));
                size -= sizeof(int*);
                dg->LaterRun(LR_CREATEBUTTON, size+sizeof(int), ptr);
cout << "  --> F " << endl; fflush(stdout);
            }
            break;
        case API_SETBUTTONTEXT:
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETBUTTONTEXT, size, ptr);
            break;
        case API_SETBUTTONENABLED:
            ptr = (char*)data+sizeof(int); // STEP
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETBUTTONENABLED, size, ptr);
            break;
        case API_DROPBUTTON:
            ptr = (char*)data+sizeof(int); // STEP
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_DROPBUTTON, size, ptr);
            break;
        case API_CREATECARDSGROUP: //NO
            for(i=0; i<20 && cardsgroups[i] != NULL; i++);
            if(i<20) {
                cardsgroups[i] = (QCards *)dg->nil;
                int *cg_id;
                ptr = (char*)data+(sizeof(int)+sizeof(int*));
                memcpy(&size, data, sizeof(int));
                memcpy(&cg_id, (char*)data+sizeof(int), sizeof(int));
                *cg_id = i;
                memcpy(ptr+(size-sizeof(int*)), &i, sizeof(int));
                size -= sizeof(int*);
                dg->LaterRun(LR_CREATECARDSGROUP, size+sizeof(int), ptr);
                printf("CreateCG %d\n",i);
            }
            break;
        /*case API_SETCARDSGROUPTEXT: //NO REAL
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETBUTTONTEXT, size, ptr);
            break;*/
        case API_SETCARDSGROUPXY: //NO
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETCARDSGROUPXY, size, ptr);
            break;
        case API_SETCARDSGROUPVERTICAL: //NO
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETCARDSGROUPVERTICAL, size, ptr);
            break;
        case API_SETCARDSGROUPCONTROL: //NO
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETCARDSGROUPCONTROL, size, ptr);
            break;
        case API_SETCARDSGROUPENABLED: //NO
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETCARDSGROUPENABLED, size, ptr);
            break;
        case API_DROPCARDSGROUP: //NO
            ptr = (char*)data+sizeof(int); // UP UP UP ??
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_CARDSGROUPDROP, size, ptr);
            break;
        case API_SETPLAYERCARDSXY: // V idon cod
            mja = (int*)(((void **)data)[2]);
            printf("test: ");
            for(int test=0; test<*(int*)(((void **)data)[1]); test++)
                printf("[%d]",mja[test]);
            printf("\n");
            Players[*(int*)(((void **)data)[0])]->LaterRun(QCARDS_CTRL_POS, *(int*)(((void **)data)[1]), (int*)(((void **)data)[2]));
            break;
        case API_SETPLAYERCARDSVERTICAL:
            Players[*(int*)(((void **)data)[0])]->LaterRun(QCARDS_CTRL_VERTICAL, *(int*)(((void **)data)[1]), (int*)(((void **)data)[2]));
            break;
        case API_SETPLAYERCARDSCONTROL:
            Players[*(int*)(((void **)data)[0])]->LaterRun(QCARDS_CTRL_CONTROL, *(int*)(((void **)data)[1]), (int*)(((void **)data)[2]));
            break;
        case API_SETPLAYERCARDSENABLED:
            Players[*(int*)(((void **)data)[0])]->LaterRun(QCARDS_CTRL_ENABLED, *(int*)(((void **)data)[1]), (int*)(((void **)data)[2]));
            break;
        case API_SIZESELPLAYERCARDS: //!!
            memcpy(&retsize, (char*)data, sizeof(int*));
            *retsize = Players[0]->countSelectCards();
            break;
        case API_GETSELPLAYERCARDS: //!!
            memcpy(&retval, (char*)data, sizeof(int*));
            printf("DialogGame %p\n", retval);
            Players[0]->getSelectCards(retval);
            break;
        case API_SIZEALLPLAYERCARDS: //!!
            memcpy(&retsize, (char*)data, sizeof(int*));
            *retsize = Players[0]->countCards();
            break;
        case API_GETALLPLAYERCARDS: //!!
            memcpy(&retval, (char*)data, sizeof(int*));
            printf("DialogGame %p\n", retval);
            Players[0]->getCards(retval);
            break;
        case API_REMFROMPLAYERCARDS:
            Players[0]->LaterRun(QCARDS_CTRL_REM, *(int*)(((void **)data)[0]), (int*)(((void **)data)[1]));
            break;
        case API_SIZESELCARDSGROUP:
            memcpy(&retsize, data, sizeof(int*));
            memcpy(&cgid, (char*)data+sizeof(int*), sizeof(int));
            *retsize = cardsgroups[cgid]->countSelectCards();
            break;
        case API_GETSELCARDSGROUP:
            memcpy(&cgid, data, sizeof(int));
            memcpy(&retval, (char*)data+sizeof(int), sizeof(int*));
            printf("DialogGame %p\n", retval);
            cardsgroups[cgid]->getSelectCards(retval);
            break;
        case API_SIZEALLCARDSGROUP:
            memcpy(&retsize, data, sizeof(int*));
            memcpy(&cgid, (char*)data+sizeof(int*), sizeof(int));
            *retsize = cardsgroups[cgid]->countCards();
            break;
        case API_GETALLCARDSGROUP:
            memcpy(&cgid, data, sizeof(int));
            memcpy(&retval, (char*)data+sizeof(int), sizeof(int*));
            printf("DialogGame %p\n", retval);
            cardsgroups[cgid]->getCards(retval);
            break;
        case API_ADDTOCARDSGROUP:
            dg->LaterRun(LR_ADDTOCG, *(int*)(((void **)data)[0])*sizeof(int), (int*)(((void **)data)[1]));
                break;
        case API_REMFROMCARDSGROUP:
                dg->LaterRun(LR_REMFROMCG, *(int*)(((void **)data)[0])*sizeof(int), (int*)(((void **)data)[1]));
                break;
        case API_SETPLAYERSCORE:
            ptr = (char*)data+sizeof(int); // STEP
            memcpy(&size, data, sizeof(int));
            dg->LaterRun(LR_SETPLAYERSCORE, size, ptr);
            break;
    }
    return;
}

void DialogGame::LaterRun(int cmd, int size, void *datablock){
    cout << "HERE!!! 4 " << endl; fflush(stdout);
    if(problems == NULL)
        prevprob = problems = new struct GameProblem;
    else
        prevprob = prevprob->next = new struct GameProblem;
    prevprob->cmd = cmd;
    prevprob->size = size;
    if(datablock!=NULL) {
        prevprob->data = new char[size];
        memcpy(prevprob->data, datablock, size);
    }
    else prevprob->data = NULL;
    prevprob->next = NULL;
}

void DialogGame::ReleaseProblems(void){
    GameProblem *p;
    int x,y,w,h,buttonid,cgid,score,number,i;
    bool mode;
    while(problems!=NULL){
        p = problems;
        problems = problems->next;
        switch(p->cmd){
                case LR_CREATEPLAYERS:
                    memcpy(&number, p->data, sizeof(int));
                    if(Players == NULL){
                        Players = new QCards*[number];
                        for(i=0; i<number; i++){
                            Players[i] = new QCards(this);
                            Players[i]->setX(100);
                            Players[i]->setY(100);
                        }
                        Players[0]->setControl(true);
                        playerscount = number;
                        core1->StartGame();
                    }
                break;
            case LR_CREATEBUTTON: // in function?
            cout << "HERE!!! 5 " << endl; fflush(stdout);
                memcpy(&x, p->data, sizeof(int));
                memcpy(&y, p->data+sizeof(int), sizeof(int));
                memcpy(&w, p->data+sizeof(int)*2, sizeof(int));
                memcpy(&h, p->data+sizeof(int)*3, sizeof(int));
                memcpy(&buttonid, p->data+(p->size-sizeof(int)), sizeof(int));
                ctrlbuttons[buttonid] = new QPushButton(dg);
                ctrlbuttons[buttonid]->setGeometry(x, y, w, h);
                ctrlbuttons[buttonid]->setText(p->data+sizeof(int)*4);
                connect(ctrlbuttons[buttonid], SIGNAL(clicked()), this, SLOT(ctrlpushButton_clicked()));
                ctrlbuttons[buttonid]->setVisible(true);
                break;
            case LR_SETBUTTONTEXT:
                memcpy(&buttonid, p->data, sizeof(int));
                if(ctrlbuttons[buttonid] == NULL) break;
                ctrlbuttons[buttonid]->setText(p->data+sizeof(int));
                break;
            case LR_SETBUTTONENABLED:
                memcpy(&buttonid, p->data, sizeof(int));
                memcpy(&mode, p->data+sizeof(int), sizeof(bool));
                if(ctrlbuttons[buttonid] == NULL) break;
                ctrlbuttons[buttonid]->setEnabled(mode);
                break;
            case LR_DROPBUTTON:
                memcpy(&buttonid, p->data, sizeof(int));
                if(ctrlbuttons[buttonid] == NULL) break;
                delete ctrlbuttons[buttonid];
                ctrlbuttons[buttonid] = NULL;
                break;
            case LR_CREATECARDSGROUP: // in function?
                printf("CREATEGROUP\n");
                fflush(stdout);
                memcpy(&x, p->data, sizeof(int));
                memcpy(&y, p->data+sizeof(int), sizeof(int));
                memcpy(&cgid, p->data+(p->size-sizeof(int)), sizeof(int));
                cardsgroups[cgid] = new QCards(dg);
                cardsgroups[cgid]->setX(x);
                cardsgroups[cgid]->setY(y);
                //cardsgroups[cgid]->addSecretCards(3);
                //cardsgroups[cgid]->setText(p->data+sizeof(int)*2);
                cardsgroups[cgid]->Change();
                break;
            case LR_SETCARDSGROUPXY:
                memcpy(&cgid, p->data, sizeof(int));
                memcpy(&x, p->data+sizeof(int), sizeof(int));
                memcpy(&y, p->data+sizeof(int)*2, sizeof(int));
                cardsgroups[cgid]->setX(x);
                cardsgroups[cgid]->setY(y);
                cardsgroups[cgid]->Change();
                break;
            case LR_SETCARDSGROUPVERTICAL:
                memcpy(&cgid, p->data, sizeof(int));
                memcpy(&mode, p->data+sizeof(int), sizeof(bool));
                cardsgroups[cgid]->setVertical(mode);
                cardsgroups[cgid]->Change();
                break;
            case LR_SETCARDSGROUPCONTROL:
                memcpy(&cgid, p->data, sizeof(int));
                memcpy(&mode, p->data+sizeof(int), sizeof(bool));
                cardsgroups[cgid]->setControl(mode);
                cardsgroups[cgid]->Change();
                break;
            case LR_SETCARDSGROUPENABLED:
                memcpy(&cgid, p->data, sizeof(int));
                memcpy(&mode, p->data+sizeof(int), sizeof(bool));
                cardsgroups[cgid]->setEnabled(mode);
                cardsgroups[cgid]->Change();
                break;
            case LR_CARDSGROUPDROP:
                memcpy(&cgid, p->data, sizeof(int));
                delete cardsgroups[cgid];
                cardsgroups[cgid] = NULL;
                break;
            case LR_SETPLAYERSCORE:
                memcpy(&score, p->data, sizeof(int));
                char Score[8];
                sprintf(Score,"%d",score);
                ui->label_4->setText(Score);
                break;
            case LR_ADDTOCG:
                number = p->size/sizeof(int)-1;
                memcpy(&cgid, p->data+sizeof(int)*number, sizeof(int));
                printf("To CG %d add\n", cgid);
                cardsgroups[cgid]->addCards((int*)p->data, number);
                cardsgroups[cgid]->Change();
                //delete rr;
                break;
            case LR_REMFROMCG: // poprav!
                number = p->size/sizeof(int)-1;
                memcpy(&cgid, p->data+sizeof(int)*number, sizeof(int));
                cardsgroups[cgid]->delCards((int*)p->data, number);
                cardsgroups[cgid]->Change();
                break;
        }
        if(p->data!=NULL) delete [] p->data;
        delete p;
    }
}

int DialogGame::ctrlButtonId(QPushButton *ptr){
    int i=0;
    while(i<10)
        if(ctrlbuttons[i]==ptr)
            return i;
        else i++;
    return -1;
}

bool DialogGame::isAllReady(void){
    int i, tc;
    for(i=0; i<ui->listWidget->count(); i++)
        if(ui->listWidget->item(i)->checkState()==Qt::Unchecked)
            return false;
    //core1->StopListen();
    tc = ui->listWidget->count();
    LaterRun(LR_CREATEPLAYERS, sizeof(int), &tc);
    return true;
}

void DialogGame::updateCards(){
    cout << "TICK!" << endl; fflush(stdout);
    int i;
    for(i=0; i<playerscount; i++)
        Players[i]->ReleaseProblems();
    ReleaseProblems();
    for(i=0; i<playerscount; i++)
        if(Players[i]->isChange())
            Players[i]->repaintCards();
    for(i=0; i<20; i++)
        if(cardsgroups[i]!=NULL && cardsgroups[i]!=nil && cardsgroups[i]->isChange())
            cardsgroups[i]->repaintCards();
}

void DialogGame::ctrlpushButton_clicked(){
    core1->CtrlButtonClick(ctrlButtonId((QPushButton *)sender()));
}

void DialogGame::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->listWidget->item(0)->setCheckState(Qt::Checked);
    core1->ConfirmOfReady();
    dg->isAllReady();
}

void DialogGame::on_pushButton_clicked()
{
    close();
}

void DialogGame::on_pushButton_3_clicked()
{
    core1->SendToChat(ui->lineEdit->text().toStdString().c_str());
    /*ui->textBrowser->append(ui->lineEdit->text());
    ui->textBrowser->append(ui->lineEdit->text().toStdString().c_str());
    printf("%s\n", ui->lineEdit->text().toStdString().c_str());*/
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}
