#include "NetworkController.h"
#include <QNetworkInterface>
#include <QStringList>
#include <QHostInfo>

NetworkController::NetworkController(QObject *xParent): QObject(xParent)
{
    mTCPServerThread = new QThread();
    mTCPServerThread->start();
    mTCPServer = new TCPServer();
    mTCPServer->moveToThread(mTCPServerThread);
    this->connect(mTCPServer,SIGNAL(incomingConnection(QTcpSocket*)),SLOT(newIncomingConnection(QTcpSocket*)));
    QMetaObject::invokeMethod(mTCPServer,
                              "initialize",
                              Qt::QueuedConnection);

    mTCPConnThread = new QThread();
    mTCPConnThread->start();

    //qRegisterMetaType<Message*>("Message*");
}

NetworkController::~NetworkController()
{

}

void NetworkController::initialize(quint16 xBindPort)
{
    QMetaObject::invokeMethod(mTCPServer,
                              "startListen",
                              Qt::QueuedConnection,
                              Q_ARG(quint16, xBindPort));
}

void NetworkController::sendMessage(const QString &xPeerAddress, const quint16 &xPeerPort, const QString &xSenderUuid, const QString &xMessageType)
{
    TCPConnection *xTCPConnection;

    /*if(mTCPConnList.contains(xMessage->getMemberUuid()) == true)
    {
        xTCPConnection = mTCPConnList.value(xMessage->getMemberUuid());
    }
    else
    {
        xTCPConnection = new TCPConnection(xPeerAddress, xPeerPort);
        this->connect(xTCPConnection,
                      SIGNAL(newMessageRecived(QString,QString)),
                      SLOT(newMessageRecived_SLOT(QString,QString)));
        mTCPConnList.insert(xMessage->getMemberUuid(), xTCPConnection);
        xTCPConnection->moveToThread(mTCPConnThread);
        QMetaObject::invokeMethod(xTCPConnection,
                                  "initialize",
                                  Qt::QueuedConnection);
    }

    QMetaObject::invokeMethod(xTCPConnection,
                              "sendMessage",
                              Qt::QueuedConnection,
                              Q_ARG(const QString, xSenderUuid),
                              Q_ARG(const QString, xMessageType),
                              Q_ARG(Message*, xMessage));
                              */
}

void NetworkController::setBindPort(quint16 xBindPort)
{
    mTCPServer->startListen(xBindPort);
}

void NetworkController::newIncomingConnection(QTcpSocket *xTcpSocket)
{
    TCPConnection *xTCPConnection;
    xTCPConnection = new TCPConnection(xTcpSocket);
    this->connect(xTCPConnection,
                  SIGNAL(newMessageRecived(QString,QString)),
                  SLOT(newMessageRecived_SLOT(QString,QString)));
    mUnknownTCPConnList.push_back(xTCPConnection);
    xTCPConnection->moveToThread(mTCPConnThread);
    QMetaObject::invokeMethod(xTCPConnection,
                              "initialize",
                              Qt::QueuedConnection);
}

void NetworkController::newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType)
{
    emit this->newMessageRecived(xReceiverUuid, xMessageType);
}
