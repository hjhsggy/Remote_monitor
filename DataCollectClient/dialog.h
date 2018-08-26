#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTimerEvent>
#include <QTcpSocket>
#include <QHostAddress>

#include "textwnd.h"
#include "tempwnd.h"
#include "abpwnd.h"
#include "stripwnd.h"

//导入头文件
#include "../Common/UserType.h"

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
    void InitCtrls();//初始化
    void DeleteCtrls();//删除控件

    void CloseFiles();
    void OpenFiles();

private:

    TextWnd     *m_ptwHR;//心率
    TextWnd		*m_ptwSpO2;//脉搏氧
    ABPWnd      *m_ptwABP;//血压
    TextWnd		*m_ptwResp;//呼吸率
    TempWnd		*m_ptwTemp;//体温

    StripWnd	*m_pswECG;
    StripWnd	*m_pswSpO2;
    StripWnd	*m_pswResp;

    QPlainTextEdit			*m_pedRev;
    QPlainTextEdit			*m_pedSend;

    QPushButton		*m_pbtnSend;
    QPushButton	    *m_pbtnLoginLogout;

    //定时器标识
    int			m_uTextTimer;
    int			m_uStripTimer;
    int         m_uSendTimer;

    FILE*			m_pfECG;
    FILE*			m_pfSpO2;
    FILE*			m_pfResp;
    NET_PACK        m_NetPack;//发送的数据包

protected:
    void timerEvent(QTimerEvent *e);
    void closeEvent(QCloseEvent *e);

private slots://槽函数
    void slotDataReceived();//处理接收数据
    void slotConnected();//处理已连接
    void slotDisconnected();//处理已断开

    void slotBtnLoginOut();//响应登录和退出按钮

private:
    Ui::Dialog *ui;
private:
    bool    m_bLogin;//是否登录

    int     m_nPort;//服务器端口
    QHostAddress    *m_pServerIP;//服务器地址
    QString         m_userName;//账号(用户名)
    QTcpSocket      *m_pSocket;
    QString         m_strMID;//监护端ID


    void NetReceive(NET_PACK *pPack);//处理网络接收数据
    void HandleLogOK(NET_PACK *pPack);//处理登录成功
    void HandleLogErr(NET_PACK *pPack);//处理登录错误
    void HandleTransmit(NET_PACK *pPack);//处理数据转发
    void HandleSrvStop(NET_PACK *pPack);//处理服务器关闭

    void UserLogin();//用户登录
    void UserLogout();//用户退出

};

#endif // DIALOG_H
