#include "IncomeTransferPriv.h"

IncomeTransferPriv::IncomeTransferPriv(QString xIPv4Address, quint16 xPort, QString xFileName, quint64 xFileSize)
{
    mIPv4Address = xIPv4Address;
    mPort = xPort;

    mBytesTottal = 0;
    mBytesCurrent = 0;

    mWaitForAccept = true;
    mTransferRecived = false;
    mTransferAccepted = false;
    mTransferRejected = false;
    mTransferAborted = false;

    mFileName = xFileName;
    mFileSize = xFileSize;

    mPackage = NULL;
}

IncomeTransferPriv::~IncomeTransferPriv()
{
}

QString IncomeTransferPriv::getIPv4Address()
{
    return mIPv4Address;
}

quint16 IncomeTransferPriv::getPort()
{
    return mPort;
}

quint64 IncomeTransferPriv::getBytesTottal()
{
    return mBytesTottal;
}

quint64 IncomeTransferPriv::getBytesCurrent()
{
    return mBytesCurrent;
}

bool IncomeTransferPriv::isWaitForAccept()
{
    return mWaitForAccept;
}

bool IncomeTransferPriv::isTransferRecived()
{
    return mTransferRecived;
}

bool IncomeTransferPriv::isTransferAccepted()
{
    return mTransferAccepted;
}

bool IncomeTransferPriv::isTransferRejected()
{
    return mTransferRejected;
}

bool IncomeTransferPriv::isTransferAborted()
{
    return mTransferAborted;
}

QString IncomeTransferPriv::getFileName()
{
    return mFileName;
}

quint64 IncomeTransferPriv::getFileSize()
{
    return mFileSize;
}

Package* IncomeTransferPriv::getPackage()
{
    if(mPackage == NULL) return new Package();
    else return mPackage;
}

void IncomeTransferPriv::acceptTransfer(QString xFileName)
{
    emit this->needAcceptTransfer(xFileName);
}

void IncomeTransferPriv::rejectTransfer()
{
    emit this->needRejectTransfer();
}

void IncomeTransferPriv::sysCompleteTransfer(Package *xPackage)
{
    mTransferRecived = true;
    mPackage = xPackage;
    emit IncomeTransfer::transferCompleted(mPackage);
}

void IncomeTransferPriv::sysAcceptTransfer(QString xFileName)
{
    mWaitForAccept = false;
    mTransferAccepted = true;

    mFileName = xFileName;

    emit IncomeTransfer::transferAccepted();
}

void IncomeTransferPriv::sysRejectTransfer()
{
    mWaitForAccept = false;
    mTransferRejected = true;

    emit IncomeTransfer::transferRejected();
}

void IncomeTransferPriv::sysAbortTransfer()
{
    mTransferAborted = true;

    emit IncomeTransfer::transferAborted();
}

void IncomeTransferPriv::sysBytesSended(quint64 xBytesCurrent, quint64 xBytesTottal)
{
    mBytesCurrent = xBytesCurrent;
    mBytesTottal = xBytesTottal;

    emit IncomeTransfer::transferProgress(mBytesCurrent, mBytesTottal);
}
