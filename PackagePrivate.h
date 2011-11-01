#ifndef PACKAGEPRIVATE_H
#define PACKAGEPRIVATE_H

#include "Package.h"

class PackagePrivate : public Package
{
public:
    PackagePrivate();
    ~PackagePrivate();

    void send();
    void recive();
    void abort();

    bool isHeaderTransferComplete();
    bool isBodyTransferComplete();
    bool isFileTransferComplete();
    bool isTransferComplete();
    bool isTransferAborted();

    QByteArray getHeaderBytes();
    QByteArray getBodyBytes();
    QByteArray getFileBytes();

    void addBytes(QByteArray xNewBytes);
};

#endif // PACKAGEPRIVATE_H
