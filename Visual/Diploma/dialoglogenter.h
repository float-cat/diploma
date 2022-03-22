#ifndef DIALOGLOGENTER_H
#define DIALOGLOGENTER_H

#include <QDialog>


namespace Ui {
class DialogLogEnter;
}

class DialogLogEnter : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogEnter(QWidget *parent = 0);
    ~DialogLogEnter();
    QString s;
    char *GetNick(void);

private:
    Ui::DialogLogEnter *ui;
    char nick[30];

public slots:
    void DialogRegShow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_lineEdit_2_textChanged(const QString &arg1);
/*signals:
    void Qsignal(QString s);*/
};

#endif // DIALOGLOGENTER_H
