#ifndef DIALOGCLAIM_H
#define DIALOGCLAIM_H

#include <QDialog>

namespace Ui {
class DialogClaim;
}

class DialogClaim : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogClaim(QWidget *parent = 0);
    ~DialogClaim();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void GameShow();

private:
    Ui::DialogClaim *ui;
};

#endif // DIALOGCLAIM_H
