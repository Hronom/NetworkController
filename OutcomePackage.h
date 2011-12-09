#ifndef OUTCOMEPACKAGE_H
#define OUTCOMEPACKAGE_H

#include "Package.h"
#include <QObject>
#include <QBuffer>
#include <QFile>

class OutcomePackage : public QObject
{
    Q_OBJECT
private:
    quint64 mBytesTottal;
    quint64 mBytesCurrent;

    bool mHeaderSended;
    bool mBodySended;
    bool mFileSended;

    QBuffer mHeader;
    QBuffer mBody;
    QFile mFile;

public:
    OutcomePackage(const Package &xPackage);
    ~OutcomePackage();

    QString getIPv4Address();
    quint16 getPort();

    bool isHeaderSended();
    bool isBodySended();
    bool isFileSended();

    QByteArray getHeaderBytes(qint64 xBytesCount);
    QByteArray getBodyBytes(qint64 xBytesCount);
    QByteArray getFileBytes(qint64 xBytesCount);

public slots:
    void acceptPackage();
    void abortPackage();
    void rejectPackage();

signals:
    void packageSended();
    void packageAccepted();
    void packageAborted();
    void packageRejected();

    void transferProgress(quint64 xBytesCurrent, quint64 xBytesTottal);
};

#endif // OUTCOMEPACKAGE_H
