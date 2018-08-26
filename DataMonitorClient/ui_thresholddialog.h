/********************************************************************************
** Form generated from reading UI file 'thresholddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRESHOLDDIALOG_H
#define UI_THRESHOLDDIALOG_H

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
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_ThresholdDialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *txtMaxHR;
    QSlider *sldMaxHR;
    QSlider *sldMinHR;
    QLabel *label_2;
    QLineEdit *txtMinHR;
    QSlider *sldMinSpO2;
    QLabel *label_3;
    QLineEdit *txtMinSpO2;
    QSlider *sldMaxResp;
    QLabel *label_4;
    QLineEdit *txtMaxResp;
    QSlider *sldMinResp;
    QLabel *label_5;
    QLineEdit *txtMinResp;
    QSlider *sldMaxTemp;
    QLabel *label_6;
    QLineEdit *txtMaxTemp;
    QSlider *sldMinTemp;
    QLineEdit *txtMinTemp;
    QLabel *label_7;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *ThresholdDialog)
    {
        if (ThresholdDialog->objectName().isEmpty())
            ThresholdDialog->setObjectName(QStringLiteral("ThresholdDialog"));
        ThresholdDialog->resize(515, 369);
        groupBox = new QGroupBox(ThresholdDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 491, 301));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 51, 16));
        txtMaxHR = new QLineEdit(groupBox);
        txtMaxHR->setObjectName(QStringLiteral("txtMaxHR"));
        txtMaxHR->setGeometry(QRect(92, 30, 91, 21));
        txtMaxHR->setReadOnly(true);
        sldMaxHR = new QSlider(groupBox);
        sldMaxHR->setObjectName(QStringLiteral("sldMaxHR"));
        sldMaxHR->setGeometry(QRect(200, 30, 271, 22));
        sldMaxHR->setTracking(true);
        sldMaxHR->setOrientation(Qt::Horizontal);
        sldMaxHR->setTickPosition(QSlider::TicksAbove);
        sldMinHR = new QSlider(groupBox);
        sldMinHR->setObjectName(QStringLiteral("sldMinHR"));
        sldMinHR->setGeometry(QRect(200, 70, 271, 22));
        sldMinHR->setTracking(true);
        sldMinHR->setOrientation(Qt::Horizontal);
        sldMinHR->setTickPosition(QSlider::TicksAbove);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 51, 16));
        txtMinHR = new QLineEdit(groupBox);
        txtMinHR->setObjectName(QStringLiteral("txtMinHR"));
        txtMinHR->setGeometry(QRect(92, 70, 91, 21));
        txtMinHR->setReadOnly(true);
        sldMinSpO2 = new QSlider(groupBox);
        sldMinSpO2->setObjectName(QStringLiteral("sldMinSpO2"));
        sldMinSpO2->setGeometry(QRect(200, 110, 271, 22));
        sldMinSpO2->setTracking(true);
        sldMinSpO2->setOrientation(Qt::Horizontal);
        sldMinSpO2->setTickPosition(QSlider::TicksAbove);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 71, 16));
        txtMinSpO2 = new QLineEdit(groupBox);
        txtMinSpO2->setObjectName(QStringLiteral("txtMinSpO2"));
        txtMinSpO2->setGeometry(QRect(92, 110, 91, 21));
        txtMinSpO2->setReadOnly(true);
        sldMaxResp = new QSlider(groupBox);
        sldMaxResp->setObjectName(QStringLiteral("sldMaxResp"));
        sldMaxResp->setGeometry(QRect(200, 150, 271, 22));
        sldMaxResp->setTracking(true);
        sldMaxResp->setOrientation(Qt::Horizontal);
        sldMaxResp->setTickPosition(QSlider::TicksAbove);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 150, 71, 16));
        txtMaxResp = new QLineEdit(groupBox);
        txtMaxResp->setObjectName(QStringLiteral("txtMaxResp"));
        txtMaxResp->setGeometry(QRect(92, 150, 91, 21));
        txtMaxResp->setReadOnly(true);
        sldMinResp = new QSlider(groupBox);
        sldMinResp->setObjectName(QStringLiteral("sldMinResp"));
        sldMinResp->setGeometry(QRect(200, 190, 271, 22));
        sldMinResp->setTracking(true);
        sldMinResp->setOrientation(Qt::Horizontal);
        sldMinResp->setTickPosition(QSlider::TicksAbove);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 190, 71, 16));
        txtMinResp = new QLineEdit(groupBox);
        txtMinResp->setObjectName(QStringLiteral("txtMinResp"));
        txtMinResp->setGeometry(QRect(92, 190, 91, 21));
        txtMinResp->setReadOnly(true);
        sldMaxTemp = new QSlider(groupBox);
        sldMaxTemp->setObjectName(QStringLiteral("sldMaxTemp"));
        sldMaxTemp->setGeometry(QRect(200, 230, 271, 22));
        sldMaxTemp->setTracking(true);
        sldMaxTemp->setOrientation(Qt::Horizontal);
        sldMaxTemp->setTickPosition(QSlider::TicksAbove);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 230, 71, 16));
        txtMaxTemp = new QLineEdit(groupBox);
        txtMaxTemp->setObjectName(QStringLiteral("txtMaxTemp"));
        txtMaxTemp->setGeometry(QRect(92, 230, 91, 21));
        txtMaxTemp->setReadOnly(true);
        sldMinTemp = new QSlider(groupBox);
        sldMinTemp->setObjectName(QStringLiteral("sldMinTemp"));
        sldMinTemp->setGeometry(QRect(200, 260, 271, 22));
        sldMinTemp->setTracking(true);
        sldMinTemp->setOrientation(Qt::Horizontal);
        sldMinTemp->setTickPosition(QSlider::TicksAbove);
        txtMinTemp = new QLineEdit(groupBox);
        txtMinTemp->setObjectName(QStringLiteral("txtMinTemp"));
        txtMinTemp->setGeometry(QRect(92, 260, 91, 21));
        txtMinTemp->setReadOnly(true);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 260, 71, 16));
        btnOK = new QPushButton(ThresholdDialog);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(260, 330, 93, 28));
        btnCancel = new QPushButton(ThresholdDialog);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(400, 330, 93, 28));

        retranslateUi(ThresholdDialog);

        QMetaObject::connectSlotsByName(ThresholdDialog);
    } // setupUi

    void retranslateUi(QDialog *ThresholdDialog)
    {
        ThresholdDialog->setWindowTitle(QApplication::translate("ThresholdDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("ThresholdDialog", "\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("ThresholdDialog", "Max HR", 0));
        label_2->setText(QApplication::translate("ThresholdDialog", "Min HR", 0));
        label_3->setText(QApplication::translate("ThresholdDialog", "Min SpO2", 0));
        label_4->setText(QApplication::translate("ThresholdDialog", "Max Resp", 0));
        label_5->setText(QApplication::translate("ThresholdDialog", "Min Resp", 0));
        label_6->setText(QApplication::translate("ThresholdDialog", "Max Temp", 0));
        label_7->setText(QApplication::translate("ThresholdDialog", "Min Temp", 0));
        btnOK->setText(QApplication::translate("ThresholdDialog", "\347\241\256\345\256\232", 0));
        btnCancel->setText(QApplication::translate("ThresholdDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class ThresholdDialog: public Ui_ThresholdDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRESHOLDDIALOG_H
