#ifndef INCOMETRANSFERPRIV_H
#define INCOMETRANSFERPRIV_H

#include "IncomeTransfer.h"

class IncomeTransferPriv : public IncomeTransfer
{
    Q_OBJECT
private:
    QString mIPv4Address;
    quint16 mPort;

    quint64 mBytesTottal;
    quint64 mBytesCurrent;

    bool mWaitForAccept;
    bool mTransferRecived;
    bool mTransferAccepted;
    bool mTransferRejected;
    bool mTransferAborted;

    QString mFileName;
    quint64 mFileSize;

    Package *mPackage;

public:
    IncomeTransferPriv(QString xIPv4Address, quint16 xPort, QString xFileName, quint64 xFileSize);
    ~IncomeTransferPriv();

    QString getIPv4Address();
    quint16 getPort();

    quint64 getBytesTottal();
    quint64 getBytesCurrent();

    bool isWaitForAccept();
    bool isTransferRecived();
    bool isTransferAccepted();
    bool isTransferRejected();
    bool isTransferAborted();

    QString getFileName();
    quint64 getFileSize();

    Package* getPackage();

    void acceptTransfer(QString xFileName);
    void rejectTransfer();

public slots:
    void sysCompleteTransfer(Package *xPackage);
    void sysAcceptTransfer(QString xFileName);
    void sysRejectTransfer();
    void sysAbortTransfer();
    void sysBytesSended(quint64 xBytesCurrent, quint64 xBytesTottal);

signals:
    void needAcceptTransfer(QString xFileName);
    void needRejectTransfer();
};

#endif // INCOMETRANSFERPRIV_H
