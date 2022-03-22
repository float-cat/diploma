#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
//#include <QtGui>
#include <QTimer>

#include "dialoglogenter.h"
#include "ui_dialoglogenter.h"
#include "dialoggame.h"

enum {
    LR_MODELISTITEM
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //tut ob'yavlyat polya //this isn't correct in public!
    char *GetNick(void);
    static void AskerDoor(int cmd, void *data);
    char *GetSelectedMode(void);


private slots:
    void on_pushButton_clicked();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QMessageBox *MsgAboutProgram;
    ModeDataItem *root, *prev;
    ModeDataItem *localmodes, *localprev;
    void AddToList(ModeData modedata);
    void AddToLocalList(ModeData modedata);
    void StartDownload();
    void FinishDownload();
    bool isInlist(ModeData modedata);

public slots:
    void DownloadShow();
    void CreateGameShow();
    void JoinShow();
    void ConnectToServer();
   // void Qslot(QString s);
};

extern MainWindow *mw;

extern char globalnick[30]; //Why needs?

#endif // MAINWINDOW_H
