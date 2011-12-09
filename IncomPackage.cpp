#include "IncomPackage.h"
#include <QDataStream>

IncomPackage::IncomPackage(QString xIPv4Address, quint16 xPort) : IncomPackage()
{
    mIPv4Address = xIPv4Address;
    mPort = xPort;

    mBodyReady = false;
    mFileReady = false;
    mPackageAccepted = false;
    mPackageReady = false;
    mPackageAborted = false;

    mCurrentState = 0;
}

IncomPackage::~IncomPackage()
{

}

QString IncomPackage::getIPv4Address()
{
    return mIPv4Address;
}

quint16 IncomPackage::getPort()
{
    return mPort;
}

void IncomPackage::recive()
{
    emit this->beginRecive();
}

void IncomPackage::reject()
{
    emit this->rejected();
}

bool IncomPackage::isBodyReady()
{
    return mBodyReady;
}

bool IncomPackage::isFileReady()
{
    return mFileReady;
}

bool IncomPackage::isPackageAccepted()
{
    return mPackageAccepted;
}

bool IncomPackage::isPackageReady()
{
    return mPackageReady;
}

bool IncomPackage::isPackageAborted()
{
    return mPackageAborted;
}

void IncomPackage::addBytes(QByteArray xNewBytes)
{
    switch(mCurrentState)
    {
    case 0:{reciveHeaderSize(xNewBytes); break;}
    case 1:{reciveHeader(xNewBytes); break;}
    case 2:{reciveBody(xNewBytes); break;}
    case 3:{reciveFile(xNewBytes); break;}
    }

    IncomPackage::mBytesRecived += xNewBytes.size();
    if(mCurrentState > 0)
        emit IncomPackage::transferProgress(IncomPackage::mBytesRecived, IncomPackage::mPackageSize);
}

void IncomPackage::reciveHeaderSize(QByteArray xNewBytes)
{
    mTempByteBuffer.append(xNewBytes);

    if(mTempByteBuffer.size() >= sizeof(qint64))
    {
        QDataStream xDataStream(mTempByteBuffer);
        xDataStream>>mHeaderSize;

        mCurrentState = 1;
    }
}

void IncomPackage::reciveHeader(QByteArray xNewBytes)
{
    mTempByteBuffer.append(xNewBytes);

    if(mTempByteBuffer.size() >= mHeaderSize)
    {
        QDataStream xDataStream(mTempByteBuffer);
        xDataStream>>mHeaderSize;
        xDataStream>>mBodySize;
        xDataStream>>IncomPackage::mFileName;
        xDataStream>>IncomPackage::mFileSize;

        IncomPackage::mPackageSize = mHeaderSize + mBodySize + IncomPackage::mFileSize;

        mTempByteBuffer.remove(0,mHeaderSize);
        mCurrentState = 2;
    }
}

void IncomPackage::reciveBody(QByteArray xNewBytes)
{
    mTempByteBuffer.append(xNewBytes);

    if(mTempByteBuffer.size() >= mBodySize)
    {
        QDataStream xDataStream(mTempByteBuffer);
        xDataStream>>IncomPackage::mBodyFields;

        mTempByteBuffer.remove(0,mBodySize);

        mFile.setFileName(IncomPackage::mFileLoc + IncomPackage::mFileName);
        mFile.open(QIODevice::WriteOnly);
        mFile.write(mTempByteBuffer);
        mTempByteBuffer.clear();
        mCurrentState = 3;
    }
}

void IncomPackage::reciveFile(QByteArray xNewBytes)
{
    if(mFile.size() <= IncomPackage::mFileSize) mFile.write(xNewBytes);
    if(mFile.size() == IncomPackage::mFileSize) mFile.close();
}


