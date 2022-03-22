#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#include <QDialog>
#include "CoreInterface/coreinterface.hpp"
#include "CoreInterface/apilist.hpp"
#include "stdlib.h"

//Test -- on
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
//Test -- off

#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "QCards/qcards.hpp"
#include <QTimer>

struct GameProblem {
    int cmd;
    int size;
    char *data;
    struct GameProblem *next;
};


enum {
    LR_CREATEPLAYERS,
    LR_CREATEBUTTON,
    LR_SETBUTTONTEXT,
    LR_SETBUTTONENABLED,
    LR_DROPBUTTON,
    LR_CREATECARDSGROUP,
    LR_SETCARDSGROUPXY,
    LR_SETCARDSGROUPVERTICAL,
    LR_SETCARDSGROUPCONTROL,
    LR_SETCARDSGROUPENABLED,
    LR_CARDSGROUPDROP,
    LR_SETPLAYERSCORE,
    LR_ADDTOCG,
    LR_REMFROMCG
};

namespace Ui {
class DialogGame;
}

class DialogGame : public QDialog
{
    Q_OBJECT

public:
    //explicit DialogGame(QWidget *parent = 0);
    explicit DialogGame(QWidget *parent = 0, char *nick = 0);
    ~DialogGame();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();
    void updateCards();
    void ctrlpushButton_clicked();

private:
    Ui::DialogGame *ui;
    static Ui::DialogGame *tmp;
    //private custom
    struct GameProblem *problems, *prevprob;
    void LaterRun(int code, int size, void *data);
    void ReleaseProblems(void);
    int ctrlButtonId(QPushButton *ptr);
    bool isAllReady(void);
    static QCards **Players;
    int playerscount;
    void *nil;
    QTimer *timer;
    static QPushButton **ctrlbuttons;
    static QCards **cardsgroups;
public:
    static void BackDoor(int code, void * data);
};

extern DialogGame *dg;

#endif // DIALOGGAME_H
