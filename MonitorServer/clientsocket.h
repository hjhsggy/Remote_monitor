#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ClientSocket(QObject *parent = 0);
    ~ClientSocket();

signals:
    void updateClients(int*,int*);
    void disconnected(int);

public slots:
    void dataReceived();
    void slotDisconnected();

public:
    QString    m_strUID;//客户端ID号
};

#endif // CLIENTSOCKET_H
