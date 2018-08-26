#include "dialog.h"
#include "ui_dialog.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QSettings>

#include "infownd.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_ptwHR = 0;
    m_ptwABP = 0;
    m_ptwResp = 0;
    m_ptwSpO2 = 0;
    m_ptwTemp =0;

    m_pswECG = 0;
    m_pswSpO2 = 0;
    m_pswResp = 0;

    m_pedRev = 0;
    m_pedSend = 0;

    m_pbtnSend = 0;
    m_pbtnLoginLogout = 0;


    this->setWindowTitle("多参数监护----数据监护端");

    //Qt::WindowFlags flags = this->windowFlags();
    //flags |= Qt::WindowStaysOnTopHint;
    //this->setWindowFlags(flags);

    this->setWindowFlags(Qt::Dialog|Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint|Qt::WindowStaysOnTopHint);

    int iTitleBarHeight = style()->pixelMetric(QStyle::PM_TitleBarHeight);  // 获取标题栏高度
    setGeometry(0, iTitleBarHeight, QApplication::desktop()->width(), QApplication::desktop()->height() - iTitleBarHeight);  // 设置窗体充满桌面客户区


    m_pSocket = NULL;

    QSettings IniRead("Monitor.ini", QSettings::IniFormat);

    //服务器端口号
    m_nPort = IniRead.value("/NET/ServerPort").toInt();

    QString strAddress = IniRead.value("/NET/ServerIp").toString();

    //服务器地址
    this->m_pServerIP = new QHostAddress();
    this->m_pServerIP->setAddress(strAddress);

    m_userName = IniRead.value("/USER/UID").toString();

    //设置为未登录
    this->m_bLogin = false;


    InitCtrls();
}

Dialog::~Dialog()
{
    DeleteCtrls();


    if(0 != InfoWnd::m_pDlgThreshold)
    {
        delete InfoWnd::m_pDlgThreshold;
        InfoWnd::m_pDlgThreshold = NULL;
    }

    delete ui;
}


void Dialog::InitCtrls()
{

    QRect rcView,rcMiddle,rcBottom,rcCtrl,rcRight;

    //间距
    int iBorder = 3;

    //rcView
    rcView = this->rect();

    rcRight = rcView;
    rcRight.setTop(rcView.height()/30);
    rcRight.setLeft(rcView.width()*4/5 + iBorder);

    //rcMiddle
    rcView.setRight(rcView.width()*4/5);

    rcMiddle = rcView;
    rcMiddle.setTop(rcView.height()/30);
    rcMiddle.setBottom(rcView.height()*4/5);


    //rcBottom
    rcBottom = rcView;
    rcBottom.setTop(rcView.height()*4/5);

    //rcCtrl
    rcCtrl  = rcMiddle;
    rcCtrl.setLeft(rcMiddle.width()*4/5);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/5 - iBorder);


    //HR
    m_ptwHR = new TextWnd(this,rcCtrl);

    rcCtrl.setTop(rcCtrl.top() + rcMiddle.height()/5);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/5 - iBorder);

    //SpO2
    m_ptwSpO2 = new TextWnd(this,rcCtrl);
    m_ptwSpO2->setTitle(tr("脉搏氧"));
    m_ptwSpO2->setTextColor(QColor::fromRgb(255,0,0));


    rcCtrl.setTop(rcCtrl.top() + rcMiddle.height()/5);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/5 - iBorder);

    //ABP
    m_ptwABP = new ABPWnd(this,rcCtrl);
    m_ptwABP->setTextFont(16,16);
    m_ptwABP->setTitle(tr("血压"));

    rcCtrl.setTop(rcCtrl.top() + rcMiddle.height()/5);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/5 - iBorder);

    //Resp
    m_ptwResp = new TextWnd(this,rcCtrl);
    m_ptwResp->setTitle(tr("呼吸率"));
    m_ptwResp->setTextColor(qRgb(255,255,0));


    rcCtrl.setTop(rcCtrl.top() + rcMiddle.height()/5);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/5);

    //Temp
    m_ptwTemp = new TempWnd(this,rcCtrl);
    m_ptwTemp->setTitle(tr("体温"));
    m_ptwTemp->setTextColor(qRgb(255,128,0));

    //Strip
    rcCtrl = rcMiddle;
    rcCtrl.setTop(rcView.height()/30);
    rcCtrl.setRight(rcMiddle.width()*4/5 - iBorder);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/3 - iBorder);

    m_pswECG = new StripWnd(this,rcCtrl);

    //设置偏移量
    m_pswECG->SetStripOffSet(-60);

    //m_pswECG.SetStripColor(qRgb(255,0,0));

    //Sp02
    rcCtrl.setTop(rcCtrl.top() + rcMiddle.height()/3);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/3 - iBorder);

    m_pswSpO2 = new StripWnd(this,rcCtrl);
    m_pswSpO2->SetStripColor(qRgb(255,0,0));
    //设置偏移量
    m_pswSpO2->SetStripOffSet(-80);

    //Resp
    rcCtrl.setTop(rcCtrl.top() + rcMiddle.height()/3);
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/3);

    m_pswResp = new StripWnd(this,rcCtrl);
    m_pswResp->SetStripColor(qRgb(255,255,0));
    //设置偏移量
    m_pswResp->SetStripOffSet(50);


    //Edit
    rcCtrl = rcBottom;
    rcCtrl.setTop(rcMiddle.bottom());
    rcCtrl.setRight(rcBottom.width()/3);

    m_pedRev = new QPlainTextEdit(this);
    m_pedRev->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_pedRev->setGeometry(rcCtrl);

    rcCtrl.setLeft(rcBottom.width()/3 + iBorder);
    rcCtrl.setRight(rcBottom.width()*2/3);

    m_pedSend = new QPlainTextEdit(this);
    m_pedSend->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_pedSend->setGeometry(rcCtrl);

    //Button
    rcCtrl.setLeft(rcBottom.width() * 2 / 3 + iBorder);
    rcCtrl.setTop(rcBottom.bottom() - 23);
    rcCtrl.setRight(rcCtrl.left() + 60);
    rcCtrl.setBottom(rcBottom.bottom() - iBorder);

    m_pbtnLoginLogout = new QPushButton("登录",this);
    m_pbtnLoginLogout->setGeometry(rcCtrl);

    rcCtrl.setLeft(rcBottom.right() - 63);
    rcCtrl.setTop(rcBottom.bottom() - 23);
    rcCtrl.setRight(rcCtrl.left() + 60);
    rcCtrl.setBottom(rcBottom.bottom() - iBorder);

    m_pbtnSend = new QPushButton("发送",this);
    m_pbtnSend->setGeometry(rcCtrl);
    m_pbtnSend->setEnabled(false);

    //设置信号和槽
    connect(m_pbtnLoginLogout,SIGNAL(clicked()),this,SLOT(slotBtnLoginOut()));

    //读取ini文件
    QSettings IniRead("Monitor.ini", QSettings::IniFormat);

    //InfoWnd
    for(int i=0;i<CIW_COL*CIW_ROW;i++)
    {
        QRect  rcCtrl;
        rcCtrl.setLeft(rcRight.left() + (i%2)*rcRight.width()/CIW_COL);
        rcCtrl.setTop(rcRight.top() + (i/2)*rcRight.height()/CIW_ROW);
        rcCtrl.setRight(rcCtrl.left() +rcRight.width()/CIW_COL - iBorder);
        rcCtrl.setBottom(rcCtrl.top() + rcRight.height()/CIW_ROW - iBorder);

        InfoWnd* pInfoWnd = new InfoWnd(this,rcCtrl);

        //读取阈值
        THRESHOLD thd;
        QString strKeyName;

        strKeyName.sprintf("/THRESHOLD/HRMin%02d", i+1);
        thd.HRMin = IniRead.value(strKeyName).toInt();

        strKeyName.sprintf("/THRESHOLD/HRMax%02d", i+1);
        thd.HRMax = IniRead.value(strKeyName).toInt();

        strKeyName.sprintf("/THRESHOLD/SpO2Min%02d", i+1);
        thd.SpO2Min = IniRead.value(strKeyName).toInt();

        strKeyName.sprintf("/THRESHOLD/RespMin%02d", i+1);
        thd.RespMin = IniRead.value(strKeyName).toInt();

        strKeyName.sprintf("/THRESHOLD/RespMax%02d", i+1);
        thd.RespMax = IniRead.value(strKeyName).toInt();

        strKeyName.sprintf("/THRESHOLD/TempMin%02d", i+1);
        thd.TempMin = IniRead.value(strKeyName).toFloat();

        strKeyName.sprintf("/THRESHOLD/TempMax%02d", i+1);
        thd.TempMax = IniRead.value(strKeyName).toFloat();

        //设置阈值
        pInfoWnd->SetThreshold(thd);

        InfoWnd::m_InfoWndList.push_back(pInfoWnd);
    }

}

void Dialog::DeleteCtrls()
{
    if(0 != m_ptwHR)
    {
        delete m_ptwHR;
        m_ptwHR = 0;
    }
    if(0 != m_ptwSpO2)
    {
        delete m_ptwSpO2;
        m_ptwSpO2 = 0;
    }

    if(0 != m_ptwABP)
    {
        delete m_ptwABP;
        m_ptwABP = 0;
    }

    if(0 != m_ptwResp)
    {
        delete m_ptwResp;
        m_ptwResp = 0;
    }

    if(0 != m_ptwTemp)
    {
        delete m_ptwTemp;
        m_ptwTemp = 0;
    }

    if(0 != m_pswECG)
    {
        delete m_pswECG;
        m_pswECG = 0;
    }

    if(0 != m_pswResp)
    {
        delete m_pswResp;
        m_pswResp = 0;
    }

    if(0 != m_pswSpO2)
    {
        delete m_pswResp;
        m_pswResp = 0;
    }

    if(0 != m_pedRev)
    {
        delete m_pedRev;
        m_pedRev = 0;
    }

    if(0 != m_pedSend)
    {
        delete m_pedSend;
        m_pedSend = 0;
    }

    if(0 != m_pbtnLoginLogout)
    {
        delete m_pbtnLoginLogout;
        m_pbtnLoginLogout = 0;
    }

    if(0 != m_pbtnSend)
    {
        delete m_pbtnSend;
        m_pbtnSend = 0;
    }

    //写入ini文件
    QSettings IniFile("Monitor.ini", QSettings::IniFormat);

    //InfoWnd
    for(int i=0;i<CIW_COL*CIW_ROW;i++)
    {
        InfoWnd* pInfoWnd = (InfoWnd*)InfoWnd::m_InfoWndList.at(i);

        //保存阈值
        THRESHOLD thd;
        QString strKeyName;
        QString strKeyValue;

        thd = pInfoWnd->GetThreshold();

        strKeyName.sprintf("/THRESHOLD/HRMin%02d", i+1);
        strKeyValue.sprintf("%d", thd.HRMin);
        IniFile.setValue(strKeyName,strKeyValue);

        strKeyName.sprintf("/THRESHOLD//HRMax%02d", i+1);
        strKeyValue.sprintf("%d", thd.HRMax);
        IniFile.setValue(strKeyName,strKeyValue);

        strKeyName.sprintf("/THRESHOLD//SpO2Min%02d", i+1);
        strKeyValue.sprintf("%d", thd.SpO2Min);
        IniFile.setValue(strKeyName,strKeyValue);

        strKeyName.sprintf("/THRESHOLD/RespMin%02d", i+1);
        strKeyValue.sprintf("%d", thd.RespMin);
        IniFile.setValue(strKeyName,strKeyValue);

        strKeyName.sprintf("/THRESHOLD/RespMax%02d", i+1);
        strKeyValue.sprintf("%d", thd.RespMax);
        IniFile.setValue(strKeyName,strKeyValue);

        strKeyName.sprintf("/THRESHOLD/TempMin%02d", i+1);
        strKeyValue.sprintf("%.1f", thd.TempMin);
        IniFile.setValue(strKeyName,strKeyValue);

        strKeyName.sprintf("/THRESHOLD/TempMax%02d", i+1);
        strKeyValue.sprintf("%.1f", thd.TempMax);
        IniFile.setValue(strKeyName,strKeyValue);

        delete pInfoWnd;
        pInfoWnd = 0;
    }

    //清空
    InfoWnd::m_InfoWndList.clear();
}

//处理网络接收数据
void Dialog::NetReceive(NET_PACK *pPack)
{
    switch(pPack->fun)
    {
    case LOGINOK:
        HandleLogOK(pPack);
        break;
    case LOGINERR:
        HandleLogErr(pPack);
        break;
    case TRANSMIT:
        HandleTransmit(pPack);
        break;
    case STOPSERVER:
        HandleSrvStop(pPack);
        break;
    }

    if(NULL != pPack)
    {
        delete pPack;
        pPack = NULL;
    }
}

//处理已连接
void Dialog::slotConnected()
{
    //设置信号和槽
    connect(this->m_pSocket,SIGNAL(readyRead()),this,SLOT(slotDataReceived()));
}

//处理已断开
void Dialog::slotDisconnected()
{
    //设置连接状态为未登录
    this->m_bLogin = false;

    m_pbtnLoginLogout->setText("登录");
    m_pbtnSend->setEnabled(false);
}

//处理接收数据
void Dialog::slotDataReceived()
{
    if(m_pSocket->bytesAvailable()>0)
    {
        NET_PACK *pPack = new NET_PACK;
        memset(pPack,0,sizeof(NET_PACK));

        QByteArray qba = m_pSocket->readAll();

        NET_PACK *pPack1 = (NET_PACK *)qba.data();
        memcpy(pPack,pPack1,sizeof(NET_PACK));

        //处理网络数据接收
        NetReceive(pPack);
    }
}

//处理登录成功
void Dialog::HandleLogOK(NET_PACK *pPack)
{
    //设置为已经登录
    m_bLogin = true;

    //C000001,C000002,C000003,
    //设置所有客户端ID
    InfoWnd::SetAllCID(pPack->Content);

    m_pswECG->SetAllCID(pPack->Content);
    m_pswSpO2->SetAllCID(pPack->Content);
    m_pswResp->SetAllCID(pPack->Content);


    m_pbtnLoginLogout->setText("退出");
    m_pbtnSend->setEnabled(true);

}

//处理登录错误
void Dialog::HandleLogErr(NET_PACK *pPack)
{
    QString str(pPack->Content);
    QMessageBox::information(this,"系统提示",str);

    this->m_pSocket->close();
    this->m_pSocket->disconnectFromHost();

    delete m_pSocket;
    m_pSocket = NULL;

    m_bLogin = false;
    m_pbtnLoginLogout->setText("登录");
    m_pbtnSend->setEnabled(false);


}

//处理数据转发
void Dialog::HandleTransmit(NET_PACK *pPack)
{
    for(int i=0;i<CIW_COL*CIW_ROW;i++)
    {
        InfoWnd* pWnd = (InfoWnd*)InfoWnd::m_InfoWndList[i];

        if(pWnd->GetCID().compare(pPack->SenderID) == 0)
        {
            //将数据显示到对应的窗口
            pWnd->SetMedNum(pPack->MedNum);

            if(InfoWnd::m_pCurInfoWnd != NULL)
            {
                if(InfoWnd::m_pCurInfoWnd->GetCID().compare(pPack->SenderID) == 0)
                {
                    m_ptwHR->setNumber(pPack->MedNum.HR);
                    m_ptwSpO2->setNumber(pPack->MedNum.Sp02);
                    m_ptwABP->SetNumber(pPack->MedNum.ABPMax, pPack->MedNum.ABPMin, pPack->MedNum.ABPCur);
                    m_ptwResp->setNumber(pPack->MedNum.Resp);
                    m_ptwTemp->setNumber(pPack->MedNum.Temp);
                }
            }
        }
    }


    //保存线条数据
    m_pswECG->AddPoint(pPack->MedStrip.ECG,pPack->MedStrip.ECGLen,pPack->SenderID);
    m_pswSpO2->AddPoint(pPack->MedStrip.Sp02,pPack->MedStrip.Sp02Len,pPack->SenderID);
    m_pswResp->AddPoint(pPack->MedStrip.Resp,pPack->MedStrip.RespLen,pPack->SenderID);

}

//处理服务器关闭
void Dialog::HandleSrvStop(NET_PACK *pPack)
{
    QString str(pPack->Content);
    QMessageBox::information(this,"系统提示",str);

    this->m_pSocket->close();
    this->m_pSocket->disconnectFromHost();

    delete m_pSocket;
    m_pSocket = NULL;

    m_bLogin = false;
}

//响应登录和退出按钮
void Dialog::slotBtnLoginOut()
{
    if(!m_bLogin)
    {
        //未登录
        UserLogin();
    }
    else
    {
        //已经登录
        UserLogout();
    }


}

//用户登录
void Dialog::UserLogin()
{
    //创建Socket
    this->m_pSocket = new QTcpSocket(this);

    //设置信号和槽
    connect(this->m_pSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
    connect(this->m_pSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));

    //连接服务器
    this->m_pSocket->connectToHost(*this->m_pServerIP,this->m_nPort);

    //发送数据
    NET_PACK pack;
    memset(&pack,0,sizeof(NET_PACK));

    pack.fun = LOGIN;

    strcpy(pack.SenderID,m_userName.toStdString().c_str());

    m_pSocket->write((char*)&pack,sizeof(NET_PACK));

    //等待数据发送
    //m_pSocket->waitForBytesWritten(50);

}

//用户退出
void Dialog::UserLogout()
{
    if(NULL != m_pSocket)
    {
        //发送数据
        NET_PACK pack;
        memset(&pack,0,sizeof(NET_PACK));

        pack.fun = LOGOUT;

        strcpy(pack.SenderID,m_userName.toStdString().c_str());

        m_pSocket->write((char*)&pack,sizeof(NET_PACK));

        //等待数据发送
        m_pSocket->waitForBytesWritten(50);


        this->m_pSocket->close();
        this->m_pSocket->disconnectFromHost();


        delete m_pSocket;
        m_pSocket = NULL;
    }

    m_bLogin = false;
    m_pbtnLoginLogout->setText("登录");
    m_pbtnSend->setEnabled(false);

}

//窗口关闭事件
void Dialog::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);

    if(m_bLogin)
    {
        UserLogout();
    }

}
