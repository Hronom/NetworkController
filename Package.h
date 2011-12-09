#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QHash>

class Package : public QObject
{
    Q_OBJECT
protected:
    QHash<QString, QString> mBodyFields;
    QString mFileName;

public:
    Package();
    ~Package();

    void addBodyField(QString xKey, QString xValue);
    bool removeBodyField(QString xKey);
    QString getBodyField(QString xKey);
    QHash<QString, QString> getBodyFields();

    void attachFile(QString xFileName);
    void deattachFile();
    QString getAttachedFile();
};

#endif // PACKAGE_H
