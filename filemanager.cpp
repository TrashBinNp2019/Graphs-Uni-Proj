#include "filemanager.h"

#include <QFile>
#include <QJsonDocument>


FileManager::FileManager( QObject *parent )
    : QObject( parent )
{
}

Data *FileManager::read( const QString &filename )
{
    auto data = new Data();

    QFile file;
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        emit fileError( "Couldn't open input file");
        return data;
    }

    auto doc = file.readAll();
    data->fromJson( QJsonDocument::fromJson( doc ) );

    return data;
}

void FileManager::write( const Data &data, const QString &filename ) const{
    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ) {
        emit fileError( "Couldn't open output file");
        return;
    }

    auto doc = data.toJson().toJson();
    file.write( doc );
}
