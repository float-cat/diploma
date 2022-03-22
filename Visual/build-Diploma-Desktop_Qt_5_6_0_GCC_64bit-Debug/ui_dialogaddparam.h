/********************************************************************************
** Form generated from reading UI file 'dialogaddparam.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGADDPARAM_H
#define UI_DIALOGADDPARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAddParam
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *DialogAddParam)
    {
        if (DialogAddParam->objectName().isEmpty())
            DialogAddParam->setObjectName(QStringLiteral("DialogAddParam"));
        DialogAddParam->resize(175, 129);
        pushButton = new QPushButton(DialogAddParam);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 90, 75, 23));

        retranslateUi(DialogAddParam);

        QMetaObject::connectSlotsByName(DialogAddParam);
    } // setupUi

    void retranslateUi(QDialog *DialogAddParam)
    {
        DialogAddParam->setWindowTitle(QApplication::translate("DialogAddParam", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0));
        pushButton->setText(QApplication::translate("DialogAddParam", "\320\236\320\232", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAddParam: public Ui_DialogAddParam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDPARAM_H
