#include "dialog.h"
#include "ui_dialog.h"

#include <QTime>
#include <QMessageBox>
#include <QSettings>

#define PTCOUNT 3

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

    m_pfECG = 0;
    m_pfResp = 0;
    m_pfSpO2 = 0;

    m_pSocket = NULL;

    QSettings IniRead("Client.ini", QSettings::IniFormat);

    //服务器端口号
    m_nPort = IniRead.value("/NET/Port").toInt();

    QString strAddress = IniRead.value("/NET/ServerIp").toString();

    //服务器地址
    this->m_pServerIP = new QHostAddress();
    this->m_pServerIP->setAddress(strAddress);

    m_userName = IniRead.value("/USER/ID").toString();

    //监护端ID
    m_strMID = "";
    memset(&m_NetPack,0,sizeof(NET_PACK));
    strcpy(m_NetPack.SenderID,m_userName.toStdString().c_str());
    m_NetPack.fun = TRANSMIT;


    //设置为未登录
    this->m_bLogin = false;

    //打开文件
    OpenFiles();

    //初始化控件
    InitCtrls();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //启动定时器
    m_uTextTimer = startTimer(500);
    //注意定时器的超时间隔
    m_uStripTimer = startTimer(20);
    m_uSendTimer = startTimer(500);

}

Dialog::~Dialog()
{
    DeleteCtrls();

    delete ui;
}

//初始化
void Dialog::InitCtrls()
{
    this->setFixedSize(800,600);
    this->setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    this->setWindowTitle("数据采集----客户端");

    QRect rcView,rcMiddle,rcBottom,rcCtrl;

    //间距
    int iBorder = 3;

    //rcView
    rcView = this->rect();

    //rcMiddle
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
    rcCtrl.setBottom(rcCtrl.top() + rcMiddle.height()/5 - iBorder);

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
}


void Dialog::timerEvent(QTimerEvent *e)
{
    //文本显示定时器
    if(e->timerId() == m_uTextTimer)
    {
        int HR, SpO2, MaxABP, MinABP, CurABP, Resp;
        float Temp;
        HR		= rand() % 41 + 60;
        SpO2	= rand() % 5  + 95;
        MaxABP	= rand() % 81 + 100;
        MinABP  = rand() % 31 + 60;
        CurABP	= (MaxABP + MinABP) / 2;
        Resp	= qrand() % 9  + 16;
        Temp	= (qrand() % 81 + 340) / 10.0;

        m_ptwHR->setNumber(HR);
        m_ptwSpO2->setNumber(SpO2);
        m_ptwABP->SetNumber(MaxABP, MinABP, CurABP);
        m_ptwResp->setNumber(Resp);
        m_ptwTemp->setNumber(Temp);

        //更新发送数据包的数据
        m_NetPack.MedNum.HR = HR;
        m_NetPack.MedNum.Sp02 = SpO2;
        m_NetPack.MedNum.ABPMax=MaxABP;
        m_NetPack.MedNum.ABPCur = CurABP;
        m_NetPack.MedNum.ABPMin = MinABP;
        m_NetPack.MedNum.Resp = Resp;
        m_NetPack.MedNum.Temp = Temp;

        return;
    }

    //线条显示定时器
    if(e->timerId() == m_uStripTimer)
    {
        uchar Data[PTCOUNT];
        int iCount = fread(Data,1,PTCOUNT,m_pfECG);

        if(iCount < PTCOUNT)
        {
            //将文件指针，重置
            rewind(m_pfECG);

            fread(Data+iCount,1,PTCOUNT - iCount,m_pfECG);
        }

        //ECG
        m_pswECG->AddPoint(Data,PTCOUNT);

        //更新发送数据包中线条的数据
        if(m_bLogin)
        {
            memcpy(&m_NetPack.MedStrip.ECG[m_NetPack.MedStrip.ECGLen],Data,PTCOUNT);

            //防止数据越界
            m_NetPack.MedStrip.ECGLen = (m_NetPack.MedStrip.ECGLen +PTCOUNT) % 128;
        }

        //SpO2
        iCount = fread(Data,1,PTCOUNT,m_pfSpO2);

        if(iCount < PTCOUNT)
        {
            //讲文件指针，重置
            rewind(m_pfSpO2);

            fread(Data+iCount,1,PTCOUNT - iCount,m_pfSpO2);
        }

        //SpO2
        m_pswSpO2->AddPoint(Data,PTCOUNT);

        //更新发送数据包中线条的数据

        if(m_bLogin)
        {
            memcpy(&m_NetPack.MedStrip.Sp02[m_NetPack.MedStrip.Sp02Len],Data,PTCOUNT);
            //m_NetPack.MedStrip.Sp02Len+=PTCOUNT;

            //防止数据越界
            m_NetPack.MedStrip.Sp02Len = (m_NetPack.MedStrip.Sp02Len+PTCOUNT)%128;
        }



        //SpO2
        iCount = fread(Data,1,PTCOUNT,m_pfResp);

        if(iCount < PTCOUNT)
        {
            //讲文件指针，重置
            rewind(m_pfResp);

            fread(Data+iCount,1,PTCOUNT - iCount,m_pfResp);
        }

        //Resp
        m_pswResp->AddPoint(Data,PTCOUNT);


        if(m_bLogin)
        {
            memcpy(&m_NetPack.MedStrip.Resp[m_NetPack.MedStrip.RespLen],Data,PTCOUNT);
            //m_NetPack.MedStrip.RespLen+=PTCOUNT;

            //防止数据越界
            m_NetPack.MedStrip.RespLen = (m_NetPack.MedStrip.RespLen + PTCOUNT)%128;
        }


        return;
    }


    //发送数据定时器
    if(e->timerId() == m_uSendTimer)
    {
        if(m_bLogin)//已登陆
        {
            m_pSocket->write((char*)&m_NetPack,sizeof(NET_PACK));

            //等待数据发送
            //m_pSocket->waitForBytesWritten(50);

            m_NetPack.MedStrip.ECGLen = 0;
            m_NetPack.MedStrip.Sp02Len = 0;
            m_NetPack.MedStrip.RespLen = 0;
        }

        return;
    }

}

//关闭文件
void Dialog::CloseFiles()
{
    if(m_pfECG != 0)
    {
        fclose(m_pfECG);

        m_pfECG = 0;
    }

    if(m_pfSpO2!= 0)
    {
        fclose(m_pfSpO2);

        m_pfSpO2 = 0;
    }

    if(m_pfResp != 0)
    {
        fclose(m_pfResp);

        m_pfResp = 0;
    }

}

void Dialog::OpenFiles()
{
    if(m_pfECG == 0)
    {
        m_pfECG = fopen("1.txt","rb");

        if(m_pfECG == 0)
        {
            QMessageBox::information(this,"应用程序提示",tr("打开文件失败!"));
            return;
        }
    }

    if(m_pfSpO2 == 0)
    {
        m_pfSpO2 = fopen("2.txt","rb");

        if(m_pfSpO2 == 0)
        {
            QMessageBox::information(this,"应用程序提示",tr("打开文件失败!"));
            return;
        }
    }

    if(m_pfResp == 0)
    {
        m_pfResp = fopen("3.txt","rb");

        if(m_pfResp == 0)
        {
            QMessageBox::information(this,"应用程序提示",tr("打开文件失败!"));
            return;
        }
    }
}

//窗口关闭事件
void Dialog::closeEvent(QCloseEvent *e)
{
    if(m_bLogin)
    {
        UserLogout();
    }

    //关闭定时器
    killTimer(m_uSendTimer);
    killTimer(m_uTextTimer);
    killTimer(m_uStripTimer);


    CloseFiles();
}

//删除控件
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

    //保存监护端ID
    m_strMID = pPack->Content;

    strcpy(m_NetPack.ReverID,m_strMID.toStdString().c_str());


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
