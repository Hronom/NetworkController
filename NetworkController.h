#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QObject>
#include <QThread>

#include "TCPServer.h"
#include "TCPConnection.h"

class NetworkController: public QObject
{
    Q_OBJECT
private:
    QThread *mTCPServerThread;
    TCPServer *mTCPServer;

    QThread *mTCPConnThread;
    QHash<QString, TCPConnection*> mTCPConnList;
    QList<TCPConnection*> mUnknownTCPConnList;

public:
    NetworkController(QObject *xParent);
    ~NetworkController();

    void initialize(quint16 xBindPort);
    void sendMessage(const QString &xPeerAddress, const quint16 &xPeerPort, const QString &xSenderUuid, const QString &xMessageType);

    void setBindPort(quint16 xBindPort);

private slots:
    void newIncomingConnection(QTcpSocket *xTcpSocket);
    void newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType);

signals:
    void TCPBindStateChanged(bool xBindState);//сигнал оповещения состояния прослушивания TCP порта
    void newMessageRecived(const QString &xReceiverUuid, const QString &xMessageType);
};

#endif // NETWORKCONTROLLER_H
