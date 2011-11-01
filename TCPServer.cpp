#include "TCPServer.h"
#include <QDebug>
#include <QThread>
#include <QApplication>

TCPServer::TCPServer()
{
}

void TCPServer::initialize()
{
    mTcpServer = new QTcpServer(this);
    this->connect(mTcpServer,SIGNAL(newConnection()),this,SLOT(newIncomingConnection()));
}

void TCPServer::startListen(quint16 xBindPort)
{
    mTcpServer->close();
    bool xBindState;
    xBindState = mTcpServer->listen(QHostAddress::Any, xBindPort);

    emit this->bindStateChanged(xBindState);
}

void TCPServer::newIncomingConnection()
{
    qDebug()<<"Current"<<QThread::currentThread();
    qDebug()<<"Current"<<QObject::thread();
    while(mTcpServer->hasPendingConnections())
    {
        QTcpSocket *xTCPSocket = mTcpServer->nextPendingConnection();
        xTCPSocket->setParent(0);
        xTCPSocket->moveToThread(qApp->thread());
        emit this->incomingConnection(xTCPSocket);
    }
}
