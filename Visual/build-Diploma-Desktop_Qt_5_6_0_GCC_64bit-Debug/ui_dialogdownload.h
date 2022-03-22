/********************************************************************************
** Form generated from reading UI file 'dialogdownload.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDOWNLOAD_H
#define UI_DIALOGDOWNLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_DialogDownload
{
public:
    QPushButton *pushButton;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *DialogDownload)
    {
        if (DialogDownload->objectName().isEmpty())
            DialogDownload->setObjectName(QStringLiteral("DialogDownload"));
        DialogDownload->resize(451, 241);
        pushButton = new QPushButton(DialogDownload);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(344, 210, 91, 25));
        QFont font;
        font.setPointSize(11);
        pushButton->setFont(font);
        textBrowser = new QTextBrowser(DialogDownload);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 431, 192));

        retranslateUi(DialogDownload);

        QMetaObject::connectSlotsByName(DialogDownload);
    } // setupUi

    void retranslateUi(QDialog *DialogDownload)
    {
        DialogDownload->setWindowTitle(QApplication::translate("DialogDownload", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \320\270\320\263\321\200\321\213", 0));
        pushButton->setText(QApplication::translate("DialogDownload", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDownload: public Ui_DialogDownload {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDOWNLOAD_H
