#include "qcards.hpp"

QPushButton **QCards::collectObj = NULL;
int QCards::w = 60, QCards::h = 84;

QCards::QCards(QWidget *parent) :
    QWidget(parent)
{
    root = NULL;
    x = y = 1;
    count = 0;
    step = 10;
    isvertical = false;
    iscontrol = false;
    ischange = false;
    problems = prevprob = NULL;
}

QCards::~QCards(void){
    clearCards(root);
}

void QCards::setX(int X){
    x = X;
}

void QCards::setY(int Y){
    y = Y;
}

void QCards::clearCards(void){
    clearCards(root);
    root = NULL;
}

void QCards::clearCards(CardsItem *p){
    if(p!=NULL)
        clearCards(p->next);
    delete p;
}

void QCards::repaintCards(void){
    CardsItem *p = root;
    QRect a;
    int i = 0, length;
    length = countCards();
    if(length<1) return;
    if(!isvertical) {
        length = (length-1)*step+w;
        length = x - length/2;
    }
    else {
        length = (length-1)*step+h;
        length = y - length/2;
    }
    while(p!=NULL){
        a = p->button->geometry();
        if(!isvertical) {
            //p->button->setGeometry(length+i, y, w, h);
            a.setX(length+i);
            a.setY(y);
        }
        else {
            //p->button->setGeometry(x, length+i, w, h);
            a.setX(x);
            a.setY(length+i);
        }
        a.setWidth(w);
        a.setHeight(h);
        p->button->setGeometry(a);
        //p->button->repaint();
        p->button->raise();
        p->button->setVisible(true);
        i += step;
        p = p->next;
    }
}

void QCards::addSecretCards(int number){ //why don't work
    /*CardsItem *p = root;
    printf("addSecretCards %d\n", number);
    while(number-->0) {
        root = new CardsItem;
        root->button = new QPushButton((QWidget*)parent());
        root->button->setIcon(QIcon("cards/back.png"));
        root->button->setIconSize(QSize(w,h));
        root->button->setVisible(true);
        root->cardid = -1;
        root->next = p;
    }*/
    int test[54];
    for(int i=0; i<54; i++) test[i] = -1;
    if(number>-1) addCards(test, number);
    else delCards(test, -number);
}

void QCards::addCards(int *cards, int number){
    CardsItem *p = root, *prev;
    int i = 0;
    sortArray(cards, number);
    //to front
    if(root!=NULL){
        prev = root;
        while(i<number && cards[i]<root->cardid){
            p = root;
            root = new CardsItem;
            if(cards[i]>=0) {
                root->button = collectObj[cards[i]%54];
            }
            else {
                root->button = new QPushButton((QWidget*)parent());
                root->button->setIcon(QIcon("cards/back.png"));
                root->button->setIconSize(QSize(w,h));
                root->button->setVisible(false);
            }
            if(iscontrol)
                connect(root->button, SIGNAL(clicked()), this, SLOT(checkCards()));
            /*else
                root->button->setEnabled(false);*/
            root->cardid = cards[i++];
            count++;
            root->next = p;
        }
    }
    else { //first item
        root = new CardsItem;
        if(cards[i]>=0) {
            root->button = collectObj[cards[i]%54];
        }
        else {
            root->button = new QPushButton((QWidget*)parent());
            root->button->setIcon(QIcon("cards/back.png"));
            root->button->setIconSize(QSize(w,h));
            root->button->setVisible(false);
        }
        if(iscontrol)
            connect(root->button, SIGNAL(clicked()), this, SLOT(checkCards()));
        /*else
            root->button->setEnabled(false);*/
        root->cardid = cards[i++];
        count++;
        root->next = NULL;
        prev = root;
    }
    //to middle
    if(root->next != NULL){
        p = root; prev = root;
        while(p->next != NULL){
            prev = p;
            p = p->next;
            while(i<number && cards[i]<p->cardid){
                prev->next = new CardsItem;
                if(cards[i]>=0) prev->next->button = collectObj[cards[i]%54];
                else { //in function
                    prev->next->button = new QPushButton((QWidget*)parent());
                    prev->next->button->setIcon(QIcon("cards/back.png"));
                    prev->next->button->setIconSize(QSize(w,h));
                    prev->next->button->setVisible(false);
                }
                if(iscontrol)
                    connect(prev->next->button, SIGNAL(clicked()), this, SLOT(checkCards()));
                /*else
                    prev->next->button->setEnabled(false);*/
                prev->next->cardid = cards[i++];
                count++;
                prev->next->next = NULL;
                prev = prev->next;
            }
            prev->next = p;
        }
        prev = prev->next;
    }
    //to back
    while(i<number){
        prev->next = new CardsItem;
        if(cards[i]>=0) {
            prev->next->button = collectObj[cards[i]%54];
        }
        else {
            prev->next->button = new QPushButton((QWidget*)parent());
            prev->next->button->setIcon(QIcon("cards/back.png"));
            prev->next->button->setIconSize(QSize(w,h));
            prev->next->button->setVisible(false);
        }
        if(iscontrol)
            connect(prev->next->button, SIGNAL(clicked()), this, SLOT(checkCards()));
        /*else
            prev->next->button->setEnabled(false);*/
        prev->next->cardid = cards[i++];
        count++;
        prev->next->next = NULL;
        prev = prev->next;
    }
}

void QCards::delCards(int *cards, int number){ // ne ydaljaet -1
    printf("delCards: ");
    for(int i=0; i<number; i++)
        printf("%d ", cards[i]);
    printf("\n");
    int i=0;
    CardsItem *p, *prev;
    sortArray(cards, number);
    while(root != NULL && i<number && root->cardid == cards[i]){
        prev = root;
        root = root -> next;
        disconnect(prev->button, SIGNAL(clicked()), this, SLOT(checkCards()));
        if(prev->cardid < 0) delete prev->button;
        else prev->button->setVisible(false);
        delete prev;
        count--;
        i++;
    }
    if(root == NULL) return;
    prev = root; p=root->next;
    while(p!=NULL && i<number){
        if(p->cardid == cards[i]){
            disconnect(p->button, SIGNAL(clicked()), this, SLOT(checkCards()));
            if(p->cardid<0)
                delete p->button;
            else p->button->setVisible(false);
            i++;
            prev->next = p->next;
            delete p;
            count--;
            p = prev->next;
        }
        else {
            prev = p;
            p = p->next;
        }
    }
}

void QCards::delSecretCards(int number){
    CardsItem *p = root;
    while(number-->0 && p != NULL && p->cardid == -1){
        root = root->next;
        delete p->button;
        delete p;
        p = root;
    }
}

void QCards::openCards(int *cards, int number){
    printf("open[");
    for(int i=0; i<number; i++)
        printf("%d ", cards[i]);
    printf("]\n");
    whichHidden(cards, number);
    printf("real open[");
    for(int i=0; i<number; i++)
        printf("%d ", cards[i]);
    printf("]\n");
    delSecretCards(number);
    addCards(cards, number);
}

void QCards::whichHidden(int *cards, int &number){
    CardsItem *p = root;
    int i=0, idx=0;
    sortArray(cards, number);
    while(p!=NULL && i<number){
        printf("test wH %d & %d\n", p->cardid, cards[i]);
        if(p->cardid == cards[i]) i++;
        else if(p->cardid > cards[i]) cards[idx++] = cards[i++];
        p = p->next;
    }
    while(i<number)
        cards[idx++] = cards[i++];
    number = idx;
}

void QCards::setVertical(bool mode){
    isvertical = mode;
}

void QCards::sortArray(int *cards, int number){
    int i,j,t;
    for(i=0; i<number-1; i++)
        for(j=i+1; j<number; j++)
            if(cards[i]>cards[j]){
                t = cards[i];
                cards[i] = cards[j];
                cards[j] = t;
            }
}

int QCards::countCards(void){
    //return count;
    int result = 0;
    CardsItem *p = root;
    while(p!=NULL){
        result++;
        p = p->next;
    }
    return result;
}

void QCards::getCards(int *cards){
    int idx = 0;
    CardsItem *p = root;
    while(p!=NULL){
        cards[idx++]=p->cardid;
        p = p->next;
    }
}

int QCards::countSelectCards(){
    int result = 0;
    CardsItem *p = root;
    while(p!=NULL){
        if(isvertical?p->button->x()!=x:p->button->y()!=y)
            result++;
        p = p->next;
    }
    return result;
}

void QCards::getSelectCards(int *cards){
    int idx = 0;
    CardsItem *p = root;
    while(p!=NULL){
        if(isvertical?p->button->x()!=x:p->button->y()!=y)
            cards[idx++]=p->cardid;
        p = p->next;
    }
}

void QCards::setControl(bool mode){
    iscontrol = mode;
    //connect & disconnect
}

void QCards::LaterRun(int cmd, int size, int *cards){
    /*printf("test2: %d:%d ",cmd, size);
    for(int test=0; test<size; test++) // pochemy ne rabotaet?
        printf("[%d]",cards[test]);
    printf("\n");*/
    fflush(stdout);
    if(problems == NULL)
        prevprob = problems = new CardsProblem;
    else
        prevprob = prevprob->next = new CardsProblem;
    prevprob->cmd = cmd;
    prevprob->size = size;
    if(cards!=NULL) {
        prevprob->cards = new int[size];
        memcpy(prevprob->cards, cards, sizeof(int)*size);
    }
    else prevprob->cards = NULL;
    prevprob->next = NULL;
    printf("%d OK!\n",cmd);
}

void QCards::ReleaseProblems(void){
    CardsProblem *p;
    bool mode;
    if(problems!=NULL){
    while(problems!=NULL){
        p = problems;
        problems = problems->next;
        switch(p->cmd){
            case QCARDS_CTRL_ADD:
                addCards(p->cards, p->size);
                break;
            case QCARDS_CTRL_REM:
                delCards(p->cards, p->size);
                break;
            case QCARDS_CTRL_SADD:
                addSecretCards(p->size);
                break;
            case QCARDS_CTRL_OPEN:
                openCards(p->cards, p->size);
                break;
            case QCARDS_CTRL_POS:
                x = p->cards[0];
                y = p->cards[1];
                printf("NOW %d : %d\n",x,y);
                break;
            case QCARDS_CTRL_VERTICAL:
                memcpy(&mode, p->cards, sizeof(bool));
                setVertical(mode);
                break;
            case QCARDS_CTRL_CONTROL:
                memcpy(&mode, p->cards, sizeof(bool));
                setControl(mode);
                break;
            case QCARDS_CTRL_ENABLED:
                memcpy(&mode, p->cards, sizeof(bool));
                setEnabled(mode);
                break;
        }
        if(p->cards!=NULL) delete [] p->cards;
        printf("problem %d exec\n", p->cmd);
        delete p;
    }
    ischange = true;
    }
}

void QCards::Change(void){
    if(!ischange) ischange = true;
}

bool QCards::isChange(void){
    bool result = ischange;
    ischange = false;
    return result;
}

void QCards::initCollectObj(QWidget *block){
    int i, ia; char path[45];
    char suit[4][9];
    strcpy(suit[0], "spades");
    strcpy(suit[1], "hearts");
    strcpy(suit[2], "clubs");
    strcpy(suit[3], "diamonds");
    collectObj = new QPushButton*[54];
    ia = strlen("cards/");
    for(i=0; i<52; i++){
        strcpy(path, "cards/");
        if(i%13 < 8) path[ia] = 50+i%13;
        else switch(i%13){
            case 9: path[ia] = 'J'; break;
            case 10: path[ia] = 'Q'; break;
            case 11: path[ia] = 'K'; break;
            case 12: path[ia] = 'A'; break;
        }
        if(path[ia]!=0) path[ia+1] = 0;
        else {
            path[ia]=49; path[ia+1]=48;
            path[ia+2]=0;
        }
        strcat(path, suit[(i%54)/13]);
        strcat(path, ".png");
        collectObj[i] = new QPushButton(block);
        collectObj[i]->setIcon(QIcon(path));
        collectObj[i]->setIconSize(QSize(w,h));
        collectObj[i]->setVisible(false);
    }
    collectObj[52] = new QPushButton(block);
    collectObj[52]->setIcon(QIcon("cards/BlackJoker.png"));
    collectObj[52]->setIconSize(QSize(w,h));
    collectObj[52]->setVisible(false);
    collectObj[53] = new QPushButton(block);
    collectObj[53]->setIcon(QIcon("cards/RedJoker.png"));
    collectObj[53]->setIconSize(QSize(w,h));
    collectObj[53]->setVisible(false);
}

void QCards::releaseCollectObj(void){
    int i;
    for(i=0; i<54; i++)
        delete collectObj[i];
    delete [] collectObj;
}

void QCards::checkCards(){
    QPushButton *Sender = (QPushButton*)sender();
    QRect a = Sender->geometry();
    if(!isvertical){
        a.setY(y-((a.y()==y)?20:0));
        a.setHeight(h);
    }
    else {
        a.setX(x+((a.x()==x)?20:0));
        a.setWidth(w);
    }
    Sender->setGeometry(a);
}
