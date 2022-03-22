#include <QApplication>
#include "mainwindow.h"
#include "dialogreg.h"
#include "dialoglogenter.h"
#include "dialoggame.h"
#include "dialogjoin.h"
#include <QTextCodec>
#include "ui_mainwindow.h"
#include "ui_dialoglogenter.h"
#include "CoreInterface/coreinterface.hpp"

MainWindow *mw = NULL; // vse sozdabija v MainWindows?
DialogGame *dg = NULL;
DialogJoin *dj = NULL;
CoreInterface *core1 = NULL;
char globalnick[30];

int main(int argc, char *argv[])
{
    int exitcode;
    if(argc>1) strcpy(globalnick, argv[1]);
    else strcpy(globalnick, "None");
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    core1 = new CoreInterface(DialogGame::BackDoor, MainWindow::AskerDoor); /* Regiter back interface functions */
    dj = new DialogJoin(NULL);
    dg = new DialogGame(NULL, globalnick); //No release
    //dg->show();
    mw = new MainWindow; // error if directory ./modes and modslist not exists
    mw->show();
    exitcode = a.exec();
    /* Safe release memory after execute */
    //delete core1;
    delete dj;
    delete dg;
    delete mw;
    return exitcode;
}
