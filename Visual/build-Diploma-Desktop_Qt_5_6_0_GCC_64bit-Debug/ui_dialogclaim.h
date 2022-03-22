/********************************************************************************
** Form generated from reading UI file 'dialogclaim.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCLAIM_H
#define UI_DIALOGCLAIM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_DialogClaim
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *DialogClaim)
    {
        if (DialogClaim->objectName().isEmpty())
            DialogClaim->setObjectName(QStringLiteral("DialogClaim"));
        DialogClaim->resize(281, 318);
        pushButton = new QPushButton(DialogClaim);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 280, 93, 25));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(DialogClaim);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 250, 151, 25));
        pushButton_2->setFont(font);
        label = new QLabel(DialogClaim);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 220, 241, 16));
        QFont font1;
        font1.setPointSize(10);
        label->setFont(font1);
        textBrowser = new QTextBrowser(DialogClaim);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 20, 241, 181));
        QPalette palette;
        QBrush brush(QColor(236, 233, 216, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        textBrowser->setPalette(palette);
        textBrowser->setFrameShape(QFrame::NoFrame);

        retranslateUi(DialogClaim);

        QMetaObject::connectSlotsByName(DialogClaim);
    } // setupUi

    void retranslateUi(QDialog *DialogClaim)
    {
        DialogClaim->setWindowTitle(QApplication::translate("DialogClaim", "Dialog", 0));
        pushButton->setText(QApplication::translate("DialogClaim", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
        pushButton_2->setText(QApplication::translate("DialogClaim", "\320\222\321\201\321\202\321\203\320\277\320\270\321\202\321\214 \320\262 \320\270\320\263\321\200\321\203", 0));
        label->setText(QApplication::translate("DialogClaim", "\320\237\320\276\320\264\320\276\320\266\320\264\320\270\321\202\320\265...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogClaim: public Ui_DialogClaim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCLAIM_H
