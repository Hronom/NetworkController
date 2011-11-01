#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHash>
#include "TCPConnection.h"

class TCPServer : public QObject
{
    Q_OBJECT
private:
    QTcpServer *mTcpServer;

public:
    TCPServer();

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void startListen(quint16 xBindPort);

private slots:
    void newIncomingConnection();

signals:
    void incomingConnection(QTcpSocket *xTcpSocket);
    void bindStateChanged(bool xBindState);
};

#endif // TCPSERVER_H
