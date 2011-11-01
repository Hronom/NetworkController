#include "Package.h"
#include <QFileInfo>

Package::Package() : QObject(0)
{
    mAttachedFile = NULL;

    mHeaderTransferComplete = false;
    mBodyTransferComplete = false;
    mFileTransferComplete = false;
    mTransferComplete = false;
    mTransferAborted = false;
}

void Package::addHeaderField(QString xKey, QString xValue)
{
    mHeaderFields.insert(xKey, xValue);
}

bool Package::removeHeaderField(QString xKey)
{
    if(mHeaderFields.remove(xKey) > 0) return true;
    else return false;
}

QHash<QString, QString> Package::getHeaderFields()
{
    return mHeaderFields;
}

void Package::addBodyField(QString xKey, QString xValue)
{
    mBodyFields.insert(xKey, xValue);
}

bool Package::removeBodyField(QString xKey)
{
    if(mBodyFields.remove(xKey) > 0) return true;
    else return false;
}

QHash<QString, QString> Package::getBodyFields()
{
    return mBodyFields;
}

void Package::attachFile(QString xFileName)
{
    mFileName = xFileName;

    QFileInfo xFileInfo;
    xFileInfo.setFile(mFileName);
    mFileName = xFileInfo.fileName();
    mFileLoc = xFileInfo.absolutePath();
    mFileBaseName = xFileInfo.baseName();
    mFileSuffix = xFileInfo.suffix();
}

void Package::deattachFile()
{
    mFileName = "";
    mFileLoc = "";
    mFileBaseName = "";
    mFileSuffix = "";
}

QString Package::getAttachedFile()
{
    return mFileLoc + mFileName;
}

QString Package::getFileName()
{
    return mFileBaseName;
}

QString Package::getFileSuffix()
{
    return mFileSuffix;
}

void Package::setFileSaveLoc(QString xFullPath)
{
    mFileLoc = xFullPath;
}
