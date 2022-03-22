#ifndef DIALOGADDPARAM_H
#define DIALOGADDPARAM_H

#include <QDialog>

namespace Ui {
class DialogAddParam;
}

class DialogAddParam : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddParam(QWidget *parent = 0);
    ~DialogAddParam();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogAddParam *ui;
};

#endif // DIALOGADDITPARAM_H
