#include "thresholddialog.h"
#include "ui_thresholddialog.h"

#include "infownd.h"

ThresholdDialog::ThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThresholdDialog)
{
    ui->setupUi(this);

    ui->sldMaxHR->setRange(50, 250);
    ui->sldMaxHR->setValue(ui->sldMaxHR->minimum());
    ui->txtMaxHR->setText(QString::number(ui->sldMaxHR->value()));

    ui->sldMinHR->setRange(0, 120);
    ui->sldMinHR->setValue(ui->sldMinHR->minimum());
    ui->txtMinHR->setText(QString::number(ui->sldMinHR->value()));

    ui->sldMinSpO2->setRange(0, 95);
    ui->sldMinSpO2->setValue(ui->sldMinSpO2->minimum());
    ui->txtMinSpO2->setText(QString::number(ui->sldMinSpO2->value()));

    ui->sldMaxResp->setRange(20, 60);
    ui->sldMaxResp->setValue(ui->sldMaxResp->minimum());
    ui->txtMaxResp->setText(QString::number(ui->sldMaxResp->value()));

    ui->sldMinResp->setRange(0, 30);
    ui->sldMinResp->setValue(ui->sldMinResp->minimum());
    ui->txtMinResp->setText(QString::number(ui->sldMinResp->value()));

    ui->sldMaxTemp->setRange(300, 440);
    ui->sldMaxTemp->setValue(ui->sldMaxTemp->minimum());
    ui->txtMaxTemp->setText(QString::number(ui->sldMaxTemp->value()));

    ui->sldMinTemp->setRange(150, 380);
    ui->sldMinTemp->setValue(ui->sldMinTemp->minimum());
    ui->txtMinTemp->setText(QString::number(ui->sldMinTemp->value()));

    InitCtrls();
}

ThresholdDialog::~ThresholdDialog()
{
    delete ui;
}

//初始化
void ThresholdDialog::InitCtrls()
{
    this->setWindowTitle("设置阈值");
    this->setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint| Qt::WindowStaysOnTopHint);
}

void ThresholdDialog::SetThreshold(THRESHOLD thd)
{
    //接收有InfoWnd传来的阈值，并将其显示在界面控件中
    ui->sldMaxHR->setValue(thd.HRMax);

    ui->sldMinHR->setValue(thd.HRMin);

    ui->sldMinSpO2->setValue(thd.SpO2Min);

    ui->sldMaxResp->setValue(thd.RespMax);

    ui->sldMinResp->setValue(thd.RespMin);

    ui->sldMaxTemp->setValue(thd.TempMax*10);

    ui->sldMinTemp->setValue(thd.TempMin*10);
}

void ThresholdDialog::SetCurInfoWnd(QWidget* pWnd)
{
    m_pCurInfoWnd = pWnd;
}

void ThresholdDialog::on_btnOK_clicked()
{
    THRESHOLD thd;

    //从界面控件取得新的阈值值，存放在thd中

    thd.HRMax	= ui->sldMaxHR->value();
    thd.HRMin	= ui->sldMinHR->value();
    thd.SpO2Min	= ui->sldMinSpO2->value();
    thd.RespMax	= ui->sldMaxResp->value();
    thd.RespMin	= ui->sldMinResp->value();
    thd.TempMax	= ui->sldMaxTemp->value();
    thd.TempMin	= ui->sldMinTemp->value();

    ((InfoWnd*)m_pCurInfoWnd)->SetThreshold(thd);

    this->hide();
}

void ThresholdDialog::on_btnCancel_clicked()
{
    this->hide();
}

void ThresholdDialog::on_sldMaxHR_valueChanged(int value)
{
    ui->txtMaxHR->setText(QString::number(value));
}

void ThresholdDialog::on_sldMinHR_valueChanged(int value)
{
    ui->txtMinHR->setText(QString::number(value));
}

void ThresholdDialog::on_sldMinSpO2_valueChanged(int value)
{
    ui->txtMinSpO2->setText(QString::number(value));
}

void ThresholdDialog::on_sldMaxResp_valueChanged(int value)
{
    ui->txtMaxResp->setText(QString::number(value));
}

void ThresholdDialog::on_sldMinResp_valueChanged(int value)
{
    ui->txtMinResp->setText(QString::number(value));
}

void ThresholdDialog::on_sldMaxTemp_valueChanged(int value)
{
    ui->txtMaxTemp->setText(QString::number(value/10.0));
}

void ThresholdDialog::on_sldMinTemp_valueChanged(int value)
{
    ui->txtMinTemp->setText(QString::number(value/10.0));
}
