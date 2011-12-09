#ifndef INCOMPACKAGE_H
#define INCOMPACKAGE_H

#include <QObject>
#include <QByteArray>
#include <QFile>

class IncomPackage: public QObject
{
    Q_OBJECT
private:
    QString mIPv4Address;
    quint16 mPort;

    bool mBodyReady;
    bool mFileReady;
    bool mPackageAccepted;
    bool mPackageReady;
    bool mPackageAborted;

    qint64 mHeaderSize;
    qint64 mBodySize;
    QByteArray mTempByteBuffer;
    QFile mFile;

    int mCurrentState;

public:
    IncomPackage(QString xIPv4Address, quint16 xPort);
    ~IncomPackage();

    QString getIPv4Address();
    quint16 getPort();

    void recive();
    void reject();

    bool isBodyReady();
    bool isFileReady();
    bool isPackageAccepted();
    bool isPackageReady();
    bool isPackageAborted();

    void addBytes(QByteArray xNewBytes);
private:
    void reciveHeaderSize(QByteArray xNewBytes);
    void reciveHeader(QByteArray xNewBytes);
    void reciveBody(QByteArray xNewBytes);
    void reciveFile(QByteArray xNewBytes);

signals:
    void beginRecive();
    void rejected();
};

#endif // INCOMPACKAGE_H
