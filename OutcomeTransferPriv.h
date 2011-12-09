#ifndef OUTCOMETRANSFERPRIV_H
#define OUTCOMETRANSFERPRIV_H

#include "OutcomeTransfer.h"

class OutcomeTransferPriv : public OutcomeTransfer
{
    Q_OBJECT
private:
    QString mIPv4Address;
    quint16 mPort;

    quint64 mBytesTottal;
    quint64 mBytesCurrent;

    bool mWaitForAccept;
    bool mTransferSended;
    bool mTransferAccepted;
    bool mTransferRejected;
    bool mTransferAborted;

public:
    OutcomeTransferPriv(QString xIPv4Address, quint16 xPort);
    ~OutcomeTransferPriv();

    QString getIPv4Address();
    quint16 getPort();

    quint64 getBytesTottal();
    quint64 getBytesCurrent();

    bool isWaitForAccept();
    bool isTransferSended();
    bool isTransferAccepted();
    bool isTransferRejected();
    bool isTransferAborted();

    void abortTransfer();

public slots:
    void sysCompleteTransfer();
    void sysAcceptTransfer();
    void sysRejectTransfer();
    void sysAbortTransfer();
    void sysBytesSended(quint64 xBytesCurrent, quint64 xBytesTottal);

signals:
    void needAbortTransfer();
};

#endif // OUTCOMETRANSFERPRIV_H
