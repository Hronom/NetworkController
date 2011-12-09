#include "OutcomeTransferPriv.h"

OutcomeTransferPriv::OutcomeTransferPriv(QString xIPv4Address, quint16 xPort)
{
    mIPv4Address = xIPv4Address;
    mPort = xPort;

    mBytesTottal = 0;
    mBytesCurrent = 0;

    mWaitForAccept = true;
    mTransferCompleted = false;
    mTransferAccepted = false;
    mTransferRejected = false;
    mTransferAborted = false;
}

OutcomeTransferPriv::~OutcomeTransferPriv()
{
}

QString OutcomeTransferPriv::getIPv4Address()
{
    return mIPv4Address;
}

quint16 OutcomeTransferPriv::getPort()
{
    return mPort;
}

quint64 OutcomeTransferPriv::getBytesTottal()
{
    return mBytesTottal;
}

quint64 OutcomeTransferPriv::getBytesCurrent()
{
    return mBytesCurrent;
}

bool OutcomeTransferPriv::isWaitForAccept()
{
    return mWaitForAccept;
}

bool OutcomeTransferPriv::isTransferSended()
{
    return mTransferCompleted;
}

bool OutcomeTransferPriv::isTransferAccepted()
{
    return mTransferAccepted;
}

bool OutcomeTransferPriv::isTransferRejected()
{
    return mTransferRejected;
}

bool OutcomeTransferPriv::isTransferAborted()
{
    return mTransferAborted;
}

void OutcomeTransferPriv::abortTransfer()
{
    emit this->needAbortTransfer();
}

void OutcomeTransferPriv::sysCompleteTransfer()
{
    mTransferCompleted = true;
    emit OutcomeTransfer::transferCompleted();
}

void OutcomeTransferPriv::sysAcceptTransfer()
{
    mWaitForAccept = false;
    mTransferAccepted = true;
    emit OutcomeTransfer::transferAccepted();
}

void OutcomeTransferPriv::sysRejectTransfer()
{
    mWaitForAccept = false;
    mTransferRejected = true;
    emit OutcomeTransfer::transferRejected();
}

void OutcomeTransferPriv::sysAbortTransfer()
{
    mTransferAborted = true;
    emit OutcomeTransfer::transferAborted();
}

void OutcomeTransferPriv::sysBytesSended(quint64 xBytesCurrent, quint64 xBytesTottal)
{
    mBytesCurrent = xBytesCurrent;
    mBytesTottal = xBytesTottal;
    emit OutcomeTransfer::transferProgress(mBytesCurrent, mBytesTottal);
}


