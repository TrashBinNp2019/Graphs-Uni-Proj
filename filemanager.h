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
    void write( const Data&, const QString& ) const;

signals:
    void fileError( const QString& ) const;
    void writeSuccess() const;
    void readSuccess() const;
};

#endif // FILEMANAGER_H
