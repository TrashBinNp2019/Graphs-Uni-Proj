#include "data.h"

#include <QJsonArray>
#include <QJsonObject>

Data::Data( QObject *parent )
    : QObject( parent )
{

}

Data *Data::operator<<( const DataElement &element )
{
    elements.append( element );
    return this;
}

QList< Data::DataElement >::iterator Data::begin()
{
    return elements.begin();
}

QList< Data::DataElement >::iterator Data::end()
{
    return elements.end();
}

QJsonDocument Data::toJson() const
{
    QJsonDocument doc;

    QJsonArray arr;
    for ( auto const &e : elements ) {
        QJsonObject obj;
        obj[ "name" ] = e.name;
        obj[ "info" ] = e.info.toJsonObject();

        arr.append( obj );
    }

    return doc;
}

void Data::fromJson( const QJsonDocument &doc )
{

}
