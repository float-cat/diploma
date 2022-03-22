#ifndef DIALOGJOIN_H
#define DIALOGJOIN_H

#include <QDialog>
#include <QListWidgetItem>
#include "utils/apilist.hpp"

namespace Ui {
class DialogJoin;
}

class DialogJoin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogJoin(QWidget *parent = 0);
    ~DialogJoin();
    void ClearGameList(void);
    void AddToList(GameData gamedata);

private:
    Ui::DialogJoin *ui;
    GameDataItem *root, *prev;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void Claim();
    void on_listWidget_itemClicked(QListWidgetItem *item);
};

extern DialogJoin *dj;

#endif // DIALOGJOIN_H
