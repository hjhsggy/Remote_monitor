#include "listensocket.h"


QList<ClientSocket*>    ListenSocket::m_listClient;

ListenSocket::ListenSocket(QObject *parent,int port):QTcpServer(parent)
{
    //开始监听
    this->listen(QHostAddress::Any,port);

    //设置信号和槽（处理新的连接请求）
    connect(this,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

ListenSocket::~ListenSocket()
{

}

//处理新的连接请求
void ListenSocket::acceptConnection()
{
    //创建负责和客户端通信的Socket
    ClientSocket *TCPsocket = new ClientSocket(this);


    connect(TCPsocket,SIGNAL(updateClients(int*,int *)),this,SLOT(updateClients(int*,int *)));
    connect(TCPsocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));

    //设置SOCKET描述符
    TCPsocket->setSocketDescriptor(this->nextPendingConnection()->socketDescriptor());
}

//更新客户端（将数据信息传送到主窗口）
void ListenSocket::updateClients(int *pData,int *pClient)
{
    //发射信号
    emit updateServer(pData,pClient);
}

//处理客户端断开连接
void ListenSocket::slotDisconnected(int descriptor)
{
    for(int i =0;i<m_listClient.count();i++)
    {
        QTcpSocket *item = m_listClient.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            //从链表中移除
            m_listClient.removeAt(i);
            return;
        }
    }
    return;
}
