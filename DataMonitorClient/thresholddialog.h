#ifndef THRESHOLDDIALOG_H
#define THRESHOLDDIALOG_H

#include <QDialog>
#include "../Common/UserType.h"

namespace Ui {
class ThresholdDialog;
}

class ThresholdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThresholdDialog(QWidget *parent = 0);
    ~ThresholdDialog();

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();

    void on_sldMaxHR_valueChanged(int value);

    void on_sldMinHR_valueChanged(int value);

    void on_sldMinSpO2_valueChanged(int value);

    void on_sldMaxResp_valueChanged(int value);

    void on_sldMinResp_valueChanged(int value);

    void on_sldMaxTemp_valueChanged(int value);

    void on_sldMinTemp_valueChanged(int value);

public:
    void SetThreshold(THRESHOLD thd);
    void SetCurInfoWnd(QWidget* pWnd);

private:
    void InitCtrls();//初始化

    QWidget*	m_pCurInfoWnd;


private:
    Ui::ThresholdDialog *ui;
};

#endif // THRESHOLDDIALOG_H
