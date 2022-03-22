#ifndef DIALOGCREATEGAME_H
#define DIALOGCREATEGAME_H

#include <QDialog>
#include <QtGui>
#include "dialoggame.h"

namespace Ui {
class DialogCreateGame;
}

class DialogCreateGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateGame(QWidget *parent = 0);
    ~DialogCreateGame();

private:
    Ui::DialogCreateGame *ui;

public slots:
    void AddParamShow();
    void GameShow1();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // DIALOGCREATEGAME_H
