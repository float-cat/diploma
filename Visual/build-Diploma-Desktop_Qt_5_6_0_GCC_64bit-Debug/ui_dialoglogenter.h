/********************************************************************************
** Form generated from reading UI file 'dialoglogenter.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGENTER_H
#define UI_DIALOGLOGENTER_H

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

class Ui_DialogLogEnter
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *DialogLogEnter)
    {
        if (DialogLogEnter->objectName().isEmpty())
            DialogLogEnter->setObjectName(QStringLiteral("DialogLogEnter"));
        DialogLogEnter->setWindowModality(Qt::WindowModal);
        DialogLogEnter->resize(221, 176);
        label = new QLabel(DialogLogEnter);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 81, 16));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(DialogLogEnter);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 81, 31));
        label_2->setFont(font);
        lineEdit = new QLineEdit(DialogLogEnter);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 30, 201, 20));
        lineEdit_2 = new QLineEdit(DialogLogEnter);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 90, 201, 20));
        pushButton = new QPushButton(DialogLogEnter);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(70, 110, 141, 23));
        pushButton->setCheckable(false);
        pushButton->setFlat(true);
        pushButton_2 = new QPushButton(DialogLogEnter);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 140, 75, 25));
        QFont font1;
        font1.setPointSize(11);
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(DialogLogEnter);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(110, 140, 75, 25));
        pushButton_3->setFont(font1);

        retranslateUi(DialogLogEnter);

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(DialogLogEnter);
    } // setupUi

    void retranslateUi(QDialog *DialogLogEnter)
    {
        DialogLogEnter->setWindowTitle(QApplication::translate("DialogLogEnter", "\320\222\321\205\320\276\320\264", 0));
        label->setText(QApplication::translate("DialogLogEnter", "\320\233\320\276\320\263\320\270\320\275", 0));
        label_2->setText(QApplication::translate("DialogLogEnter", "\320\237\320\260\321\200\320\276\320\273\321\214", 0));
        pushButton->setText(QApplication::translate("DialogLogEnter", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217?", 0));
        pushButton_2->setText(QApplication::translate("DialogLogEnter", "\320\222\321\205\320\276\320\264", 0));
        pushButton_3->setText(QApplication::translate("DialogLogEnter", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogLogEnter: public Ui_DialogLogEnter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGENTER_H
