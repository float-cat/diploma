#ifndef DIALOGREG_H
#define DIALOGREG_H

#include <QDialog>
#include <QtGui>

namespace Ui {
class DialogReg;
}

class DialogReg : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReg(QWidget *parent = 0);
    ~DialogReg();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DialogReg *ui;
};

#endif // DIALOGREG_H
