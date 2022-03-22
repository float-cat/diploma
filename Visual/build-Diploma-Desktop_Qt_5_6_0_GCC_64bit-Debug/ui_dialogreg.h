/********************************************************************************
** Form generated from reading UI file 'dialogreg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREG_H
#define UI_DIALOGREG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogReg
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;

    void setupUi(QDialog *DialogReg)
    {
        if (DialogReg->objectName().isEmpty())
            DialogReg->setObjectName(QStringLiteral("DialogReg"));
        DialogReg->setWindowModality(Qt::WindowModal);
        DialogReg->resize(321, 424);
        label = new QLabel(DialogReg);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 71, 16));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label_2 = new QLabel(DialogReg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 101, 16));
        label_2->setFont(font);
        label_3 = new QLabel(DialogReg);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 81, 16));
        label_3->setFont(font);
        label_4 = new QLabel(DialogReg);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 160, 91, 16));
        label_4->setFont(font);
        label_5 = new QLabel(DialogReg);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 210, 241, 16));
        label_5->setFont(font);
        label_6 = new QLabel(DialogReg);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 260, 151, 16));
        label_6->setFont(font);
        label_7 = new QLabel(DialogReg);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 310, 81, 16));
        label_7->setFont(font);
        label_8 = new QLabel(DialogReg);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 350, 291, 31));
        QFont font1;
        font1.setPointSize(8);
        label_8->setFont(font1);
        pushButton = new QPushButton(DialogReg);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 390, 91, 25));
        QFont font2;
        font2.setPointSize(11);
        pushButton->setFont(font2);
        pushButton_2 = new QPushButton(DialogReg);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(214, 390, 91, 25));
        pushButton_2->setFont(font2);
        pushButton_2->setFlat(false);
        lineEdit = new QLineEdit(DialogReg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 301, 20));
        lineEdit_2 = new QLineEdit(DialogReg);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 80, 301, 20));
        lineEdit_3 = new QLineEdit(DialogReg);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(10, 130, 301, 20));
        lineEdit_4 = new QLineEdit(DialogReg);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(10, 180, 301, 20));
        lineEdit_5 = new QLineEdit(DialogReg);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(10, 230, 301, 20));
        lineEdit_6 = new QLineEdit(DialogReg);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(10, 280, 301, 20));
        lineEdit_7 = new QLineEdit(DialogReg);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(10, 330, 301, 20));

        retranslateUi(DialogReg);

        pushButton_2->setDefault(false);


        QMetaObject::connectSlotsByName(DialogReg);
    } // setupUi

    void retranslateUi(QDialog *DialogReg)
    {
        DialogReg->setWindowTitle(QApplication::translate("DialogReg", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", 0));
        label->setText(QApplication::translate("DialogReg", "\320\230\320\274\321\217*", 0));
        label_2->setText(QApplication::translate("DialogReg", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217*", 0));
        label_3->setText(QApplication::translate("DialogReg", "\320\233\320\276\320\263\320\270\320\275*", 0));
        label_4->setText(QApplication::translate("DialogReg", "\320\237\320\260\321\200\320\276\320\273\321\214*", 0));
        label_5->setText(QApplication::translate("DialogReg", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\266\320\264\320\265\320\275\320\270\320\265 \320\277\320\260\321\200\320\276\320\273\321\217*", 0));
        label_6->setText(QApplication::translate("DialogReg", "\320\223\320\276\320\264 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", 0));
        label_7->setText(QApplication::translate("DialogReg", "\320\223\320\276\321\200\320\276\320\264", 0));
        label_8->setText(QApplication::translate("DialogReg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\237\320\276\320\273\321\217, \320\276\321\202\320\274\320\265\321\207\320\265\320\275\320\275\321\213\320\265 \320\267\320\262\320\265\320\267\320\264\320\276\321\207\320\272\320\276\320\271, </p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\276\320\261\321\217\320\267\320\260\321\202\320\265\320\273\321\214\320\275\321\213 \320\272 \320\267\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\216</p></body></html>", 0));
        pushButton->setText(QApplication::translate("DialogReg", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", 0));
        pushButton_2->setText(QApplication::translate("DialogReg", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogReg: public Ui_DialogReg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREG_H
