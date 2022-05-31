#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>

#include "data.h"


class FileManager : public QObject
{
    Q_OBJECT

public:
    FileManager( QObject * = nullptr );

    Data *read( const QString& );
    void write(const Data *, const QString& );

signals:
    void fileError( const QString& );
    void writeSuccess();
    void readSuccess();
};

#endif // FILEMANAGER_H
