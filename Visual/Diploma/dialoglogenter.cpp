#include "dialoglogenter.h"
#include "ui_dialoglogenter.h"

#include "dialogreg.h"
#include "ui_dialogreg.h"

#include "ui_mainwindow.h"
#include "mainwindow.h"

DialogLogEnter::DialogLogEnter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogEnter)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(DialogRegShow()));
   // connect(this,SIGNAL(Qsignal(QString)),parent,SLOT(MainWindow::Qslot));
    nick[0] = 0;
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}


DialogLogEnter::~DialogLogEnter()
{
    delete ui;
}

char * DialogLogEnter::GetNick(void)
{
    return nick;
}

void DialogLogEnter::DialogRegShow()
{
    DialogReg *dr = new DialogReg(this);
   // f->close();
    dr->open();
  //  close();
}

void DialogLogEnter::on_pushButton_clicked()
{
    this->setVisible(false);
}

void DialogLogEnter::on_pushButton_2_clicked()
{
    //emit Qsignal(ui->lineEdit->text());
    //emit close();
    RegData forsend;
    forsend.fname[0] = 0;
    forsend.sname[0] = 0;
    forsend.hash[0] = 0;
    strcpy(forsend.nick, ui->lineEdit->text().toStdString().c_str());
    core1->RegLog(forsend, 0);
    //
    strcpy(nick, ui->lineEdit->text().toStdString().c_str());
    close();
}

void DialogLogEnter::on_pushButton_3_clicked()
{
    close(); // which affect?
    exit(0);
}

void DialogLogEnter::on_lineEdit_2_textChanged(const QString &arg1)
{
  //ui->lineEdit_2->setEchoMode(QLineEdit::Password); // every change!
}
