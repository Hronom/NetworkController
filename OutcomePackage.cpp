#include "OutcomePackage.h"
#include <QDataStream>
#include <QFileInfo>

OutcomePackage::OutcomePackage(const Package &xPackage) : OutcomPackage()
{
    mHeaderSended = false;
    mBodySended = false;
    mFileSended = false;



    mBody.open(QIODevice::WriteOnly);
    QDataStream xBodyStream(&mBody);
    xBodyStream.setVersion(QDataStream::Qt_4_7);
    xBodyStream<<xPackage.getBodyFields();
    mBody.close();

    mFile.setFileName(xPackage.getAttachedFile());
    QFileInfo xAttachedFileInfo(mFile);

    mHeader.open(QIODevice::WriteOnly);
    QDataStream xHeaderStream(&mHeader);
    xHeaderStream.setVersion(QDataStream::Qt_4_7);
    xHeaderStream<<qint64(0);//оставляем место для размера заголовка
    xHeaderStream<<mBody.size();
    xHeaderStream<<xAttachedFileInfo.fileName();
    xHeaderStream<<mFile.size();
    xHeaderStream.device()->seek(0);
    xHeaderStream<<mHeader.size();
    mHeader.close();



    mBytesTottal = mHeader.size() + mBody.size() + mFile.size();
    mBytesCurrent = 0;
}

OutcomePackage::~OutcomePackage()
{
}


bool OutcomePackage::isHeaderSended()
{
    return mHeaderSended;
}

bool OutcomePackage::isBodySended()
{
    return mBodySended;
}

bool OutcomePackage::isFileSended()
{
    return mFileSended;
}

QByteArray OutcomePackage::getHeaderBytes(qint64 xBytesCount)
{
    QByteArray xTempBytes;
    xTempBytes = mHeader.read(xBytesCount);
    mBytesCurrent += xTempBytes.size();
    emit this->transferProgress(mBytesCurrent,mBytesTottal);
    if( (xTempBytes.size()) < xBytesCount ) mHeaderSended = true;

    return xTempBytes;
}

QByteArray OutcomePackage::getBodyBytes(qint64 xBytesCount)
{
    QByteArray xTempBytes;
    xTempBytes = mBody.read(xBytesCount);
    mBytesCurrent += xTempBytes.size();
    emit this->transferProgress(mBytesCurrent,mBytesTottal);
    if( (xTempBytes.size()) < xBytesCount ) mBodySended = true;

    return xTempBytes;
}

QByteArray OutcomePackage::getFileBytes(qint64 xBytesCount)
{
    if(mFile.fileName() != "")
    {
        if( mFile.isOpen() != true )
            mFile.open(QIODevice::ReadOnly);

        QByteArray xTempBytes;
        xTempBytesm = File.read(xBytesCount);
        mBytesCurrent += xTempBytes.size();
        emit this->transferProgress(mBytesCurrent,mBytesTottal);
        if( (xTempBytes.size()) < xBytesCount ) mFileSended = true;
    }
    else
        mFileSended = true;

    return xTempBytes;
}

void OutcomePackage::acceptPackage()
{
    emit this->packageAccepted();
}

void OutcomePackage::abortPackage()
{
    emit this->packageAborted();
}

void OutcomePackage::rejectPackage()
{
    emit this->packageRejected();
}
