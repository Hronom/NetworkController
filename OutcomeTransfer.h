#ifndef OUTCOMETRANSFER_H
#define OUTCOMETRANSFER_H

#include <QObject>

class OutcomeTransfer : public QObject
{
    Q_OBJECT
public:
    OutcomeTransfer();
    ~OutcomeTransfer();

    virtual QString getIPv4Address() = 0;
    virtual quint16 getPort() = 0;

    virtual quint64 getBytesTottal() = 0;
    virtual quint64 getBytesCurrent() = 0;

    virtual bool isWaitForAccept() = 0;
    virtual bool isTransferSended() = 0;
    virtual bool isTransferAccepted() = 0;
    virtual bool isTransferRejected() = 0;
    virtual bool isTransferAborted() = 0;

    virtual void abortTransfer() = 0;

signals:
    void transferCompleted();
    void transferAccepted();
    void transferRejected();
    void transferAborted();
    void transferProgress(quint64 xBytesCurrent, quint64 xBytesTottal);
};

#endif // OUTCOMETRANSFER_H
