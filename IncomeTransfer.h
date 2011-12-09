#ifndef INCOMETRANSFER_H
#define INCOMETRANSFER_H

#include <QObject>
#include "Package.h"

class IncomeTransfer : public QObject
{
    Q_OBJECT
public:
    IncomeTransfer(QObject *xParent = 0);
    ~IncomeTransfer();

    virtual QString getIPv4Address() = 0;
    virtual quint16 getPort() = 0;

    virtual quint64 getBytesTottal() = 0;
    virtual quint64 getBytesCurrent() = 0;

    virtual bool isWaitForAccept() = 0;
    virtual bool isTransferRecived() = 0;
    virtual bool isTransferAccepted() = 0;
    virtual bool isTransferRejected() = 0;
    virtual bool isTransferAborted() = 0;

    virtual QString getFileName() = 0;
    virtual quint64 getFileSize() = 0;

    virtual Package* getPackage() = 0;

    virtual void acceptTransfer(QString xFileName) = 0;
    virtual void rejectTransfer() = 0;

signals:
    void transferCompleted(Package *xPackage);
    void transferAccepted();
    void transferRejected();
    void transferAborted();
    void transferProgress(quint64 xBytesCurrent, quint64 xBytesTottal);
};

#endif // INCOMETRANSFER_H
