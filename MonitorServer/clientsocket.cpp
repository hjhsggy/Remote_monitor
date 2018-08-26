#include "clientsocket.h"

#include "../Common/UserType.h"
#include <QMessageBox>

ClientSocket::ClientSocket(QObject *parent):QTcpSocket(parent)
{
    //设置信号和槽
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected()));

    m_strUID = "";
}


ClientSocket::~ClientSocket()
{

}

//数据接收
void ClientSocket::dataReceived()
{
   // while(this->bytesAvailable()>0)
    if(this->bytesAvailable()>0)
    {
        NET_PACK *pPack = new NET_PACK;
        memset(pPack,0,sizeof(NET_PACK));

        QByteArray qba = this->readAll();

        NET_PACK *pPack1 = (NET_PACK *)qba.data();
        memcpy(pPack,pPack1,sizeof(NET_PACK));


        //QString str(pPack->SenderID);
        //QMessageBox::information(0,"系统提示",str);


        emit updateClients((int*)pPack,(int*)this);
    }
}


//处理断开
void ClientSocket::slotDisconnected()
{
    //发射信号
    emit disconnected(this->socketDescriptor());
}
