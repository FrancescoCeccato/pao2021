/********************************************************************************
** Form generated from reading UI file 'dialog_entrance.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ENTRANCE_H
#define UI_DIALOG_ENTRANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Entrance
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *Dialog_Entrance)
    {
        if (Dialog_Entrance->objectName().isEmpty())
            Dialog_Entrance->setObjectName(QString::fromUtf8("Dialog_Entrance"));
        Dialog_Entrance->resize(657, 382);
        centralwidget = new QWidget(Dialog_Entrance);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Dialog_Entrance->setCentralWidget(centralwidget);

        retranslateUi(Dialog_Entrance);

        QMetaObject::connectSlotsByName(Dialog_Entrance);
    } // setupUi

    void retranslateUi(QMainWindow *Dialog_Entrance)
    {
        Dialog_Entrance->setWindowTitle(QCoreApplication::translate("Dialog_Entrance", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Entrance: public Ui_Dialog_Entrance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ENTRANCE_H
