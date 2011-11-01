#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QHash>

class Package : public QObject
{
    Q_OBJECT
private:
    QHash<QString, QString> mHeaderFields;
    QHash<QString, QString> mBodyFields;
    QString mFileName;
    QString mFileLoc;
    QString mFileBaseName;
    QString mFileSuffix;

public:
    Package();
    ~Package();

    QString getIPv4Address() = 0;
    quint16 getPort() = 0;

    void addHeaderField(QString xKey, QString xValue);
    bool removeHeaderField(QString xKey);
    QHash<QString, QString> getHeaderFields();

    void addBodyField(QString xKey, QString xValue);
    bool removeBodyField(QString xKey);
    QHash<QString, QString> getBodyFields();

    void attachFile(QString xFileName);
    void deattachFile();
    QString getAttachedFileName();
    QString getFileName();
    QString getFileSuffix();
    void setFileSaveLoc(QString xFullPath);

    void send() = 0;
    void recive() = 0;
    void abort() = 0;

    bool isHeaderTransferComplete() = 0;
    bool isBodyTransferComplete() = 0;
    bool isFileTransferComplete() = 0;
    bool isTransferComplete() = 0;
    bool isTransferAborted() = 0;

signals:
    void headerTransferCompleted();
    void bodyTransferCompleted();
    void fileTransferCompleted();
    void transferCompleted();
    void transferAborted();

    void transferProgress(quint64 xBytesCurrent, quint64 xBytesTottal);

public slots:

};

#endif // PACKAGE_H
