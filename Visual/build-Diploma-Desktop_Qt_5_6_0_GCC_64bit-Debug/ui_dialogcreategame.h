/********************************************************************************
** Form generated from reading UI file 'dialogcreategame.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCREATEGAME_H
#define UI_DIALOGCREATEGAME_H

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

class Ui_DialogCreateGame
{
public:
    QPushButton *pushButton_3;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;

    void setupUi(QDialog *DialogCreateGame)
    {
        if (DialogCreateGame->objectName().isEmpty())
            DialogCreateGame->setObjectName(QStringLiteral("DialogCreateGame"));
        DialogCreateGame->resize(240, 111);
        pushButton_3 = new QPushButton(DialogCreateGame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(130, 70, 91, 25));
        QFont font;
        font.setPointSize(11);
        pushButton_3->setFont(font);
        label = new QLabel(DialogCreateGame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 221, 31));
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(DialogCreateGame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 40, 221, 20));
        lineEdit->setMaxLength(30);
        pushButton_2 = new QPushButton(DialogCreateGame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 70, 91, 25));
        pushButton_2->setFont(font);

        retranslateUi(DialogCreateGame);

        QMetaObject::connectSlotsByName(DialogCreateGame);
    } // setupUi

    void retranslateUi(QDialog *DialogCreateGame)
    {
        DialogCreateGame->setWindowTitle(QApplication::translate("DialogCreateGame", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\270\320\263\321\200\321\203", 0));
        pushButton_3->setText(QApplication::translate("DialogCreateGame", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
        label->setText(QApplication::translate("DialogCreateGame", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\262\320\260\321\210\320\265\320\271 \320\270\320\263\321\200\321\213", 0));
        pushButton_2->setText(QApplication::translate("DialogCreateGame", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCreateGame: public Ui_DialogCreateGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCREATEGAME_H
