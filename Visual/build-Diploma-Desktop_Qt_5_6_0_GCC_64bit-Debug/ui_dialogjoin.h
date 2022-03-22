/********************************************************************************
** Form generated from reading UI file 'dialogjoin.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGJOIN_H
#define UI_DIALOGJOIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogJoin
{
public:
    QLabel *label;
    QPushButton *pushButton_2;
    QListWidget *listWidget;
    QPushButton *pushButton_3;

    void setupUi(QDialog *DialogJoin)
    {
        if (DialogJoin->objectName().isEmpty())
            DialogJoin->setObjectName(QStringLiteral("DialogJoin"));
        DialogJoin->resize(201, 306);
        label = new QLabel(DialogJoin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 181, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        pushButton_2 = new QPushButton(DialogJoin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 270, 131, 25));
        QFont font1;
        font1.setPointSize(11);
        pushButton_2->setFont(font1);
        listWidget = new QListWidget(DialogJoin);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 40, 181, 191));
        QPalette palette;
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        listWidget->setPalette(palette);
        QFont font2;
        font2.setPointSize(10);
        listWidget->setFont(font2);
        listWidget->setAutoFillBackground(false);
        listWidget->setFrameShape(QFrame::StyledPanel);
        listWidget->setFrameShadow(QFrame::Plain);
        listWidget->setLineWidth(1);
        pushButton_3 = new QPushButton(DialogJoin);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setEnabled(false);
        pushButton_3->setGeometry(QRect(40, 240, 131, 25));
        pushButton_3->setFont(font1);

        retranslateUi(DialogJoin);

        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(DialogJoin);
    } // setupUi

    void retranslateUi(QDialog *DialogJoin)
    {
        DialogJoin->setWindowTitle(QApplication::translate("DialogJoin", "\320\237\321\200\320\270\321\201\320\276\320\265\320\264\320\270\320\275\320\270\321\202\321\214\321\201\321\217 \320\272 \320\270\320\263\321\200\320\265", 0));
        label->setText(QApplication::translate("DialogJoin", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\320\265 \320\270\320\263\321\200\321\213", 0));
        pushButton_2->setText(QApplication::translate("DialogJoin", "\320\235\320\260\320\267\320\260\320\264", 0));
        pushButton_3->setText(QApplication::translate("DialogJoin", "\320\237\320\276\320\264\320\260\321\202\321\214 \320\267\320\260\321\217\320\262\320\272\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogJoin: public Ui_DialogJoin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGJOIN_H
