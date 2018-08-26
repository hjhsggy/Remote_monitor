#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QResizeEvent>
#include <QTcpSocket>
#include <QHostAddress>

#include "textwnd.h"
#include "tempwnd.h"
#include "abpwnd.h"
#include "stripwnd.h"

#include "infownd.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
private:
    void InitCtrls();
    void DeleteCtrls();

private:
    //Text
    TextWnd         *m_ptwHR;//心率
    TextWnd		    *m_ptwSpO2;//脉搏氧
    ABPWnd		    *m_ptwABP;//血压
    TextWnd         *m_ptwResp;//呼吸率
    TempWnd         *m_ptwTemp;//体温

    //Strip
    StripWnd		*m_pswECG;//心电图
    StripWnd		*m_pswSpO2;//血氧波
    StripWnd		*m_pswResp;//呼吸波

    QPlainTextEdit			*m_pedRev;
    QPlainTextEdit			*m_pedSend;

    QPushButton		*m_pbtnSend;
    QPushButton	    *m_pbtnLoginLogout;

protected:
    void closeEvent(QCloseEvent *e);

private slots://槽函数
    void slotDataReceived();//处理接收数据
    void slotConnected();//处理已连接
    void slotDisconnected();//处理已断开

    void slotBtnLoginOut();//响应登录和退出按钮
private:
    Ui::Dialog *ui;

    bool    m_bLogin;//是否登录

    int     m_nPort;//服务器端口
    QHostAddress    *m_pServerIP;//服务器地址
    QString         m_userName;//账号(用户名)
    QTcpSocket      *m_pSocket;

    NET_PACK        m_NetPack;//发送的数据包

    void NetReceive(NET_PACK *pPack);//处理网络接收数据
    void HandleLogOK(NET_PACK *pPack);//处理登录成功
    void HandleLogErr(NET_PACK *pPack);//处理登录错误
    void HandleTransmit(NET_PACK *pPack);//处理数据转发
    void HandleSrvStop(NET_PACK *pPack);//处理服务器关闭

    void UserLogin();//用户登录
    void UserLogout();//用户退出
};

#endif // DIALOG_H
