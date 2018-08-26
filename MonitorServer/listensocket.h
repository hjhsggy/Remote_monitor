#ifndef LISTENSOCKET_H
#define LISTENSOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include "clientsocket.h"


class ListenSocket : public QTcpServer
{
    Q_OBJECT
public:
    ListenSocket(QObject *parent = 0,int port = 0);
    ~ListenSocket();

    static QList<ClientSocket*>    m_listClient;//存放和客户端通信的socket

signals:

  void updateServer(int* pData,int *pClient);

public slots:
  void updateClients(int *pData,int *pClient);

  void slotDisconnected(int descriptor);
  void acceptConnection();
};

#endif // LISTENSOCKET_H
