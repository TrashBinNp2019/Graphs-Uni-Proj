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

    QFile file( filename );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        emit fileError( "Couldn't open input file");
        delete data;

        return nullptr;
    }

    auto doc = file.readAll();
    if ( !data->fromJson( QJsonDocument::fromJson( doc ) ) ) {
        emit fileError( "Invalid format" );
        delete data;

        return nullptr;
    }

    emit readSuccess();
    return data;
}

void FileManager::write( const Data *data, const QString &filename ) {
    QFile file( filename );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ) {
        emit fileError( "Couldn't open output file");
        return;
    }

    auto doc = data->toJson().toJson( QJsonDocument::Compact );
    file.write( doc );

    emit writeSuccess();
}
