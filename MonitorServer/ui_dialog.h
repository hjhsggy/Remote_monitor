/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *txtPort;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QGroupBox *groupBox_2;
    QTableWidget *tableWidgetLogs;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(603, 444);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 581, 61));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 25, 54, 20));
        txtPort = new QLineEdit(groupBox);
        txtPort->setObjectName(QStringLiteral("txtPort"));
        txtPort->setGeometry(QRect(80, 25, 113, 20));
        btnStart = new QPushButton(groupBox);
        btnStart->setObjectName(QStringLiteral("btnStart"));
        btnStart->setGeometry(QRect(400, 25, 75, 23));
        btnStop = new QPushButton(groupBox);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setGeometry(QRect(500, 25, 75, 23));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 80, 581, 361));
        tableWidgetLogs = new QTableWidget(groupBox_2);
        tableWidgetLogs->setObjectName(QStringLiteral("tableWidgetLogs"));
        tableWidgetLogs->setGeometry(QRect(10, 20, 561, 331));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("Dialog", "\346\234\215\345\212\241\345\231\250\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("Dialog", "\347\253\257\345\217\243\345\217\267\357\274\232", 0));
        btnStart->setText(QApplication::translate("Dialog", "\345\220\257\345\212\250", 0));
        btnStop->setText(QApplication::translate("Dialog", "\345\201\234\346\255\242", 0));
        groupBox_2->setTitle(QApplication::translate("Dialog", "\344\272\213\344\273\266\345\210\227\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
