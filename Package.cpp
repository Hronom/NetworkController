#include "Package.h"
#include <QDir>

Package::Package() : QObject(0)
{
    mFileName = "";
}

Package::~Package()
{

}

void Package::addBodyField(QString xKey, QString xValue)
{
    mBodyFields.insert(xKey,xVlaue);
}

bool Package::removeBodyField(QString xKey)
{
    return mBodyFields.remove(xKey);
}

QString Package::getBodyField(QString xKey)
{
    return mBodyFields.value(xKey);
}

QHash<QString, QString> Package::getBodyFields()
{
    return mBodyFields;
}

void Package::attachFile(QString xFileName)
{
    mFileName = xFileName;
}

void Package::deattachFile()
{
    mFileName = "";
}

QString Package::getAttachedFile()
{
    return mFileName;
}
