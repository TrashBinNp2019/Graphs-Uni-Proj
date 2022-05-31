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
    QJsonArray arr;
    for ( auto const &e : elements ) {
        QJsonObject obj;
        obj[ "name" ] = e.name;
        obj[ "info" ] = e.info.toJsonObject();

        arr.append( obj );
    }

    QJsonObject obj;
    obj[ "elements" ] = arr;
    obj[ "title" ] = title;

    QJsonDocument doc{ obj };
    return doc;
}

bool Data::fromJson( const QJsonDocument &doc )
{
    elements.clear();

    if ( !doc.isObject() ) return false;
    auto obj = doc.object();

    if ( !obj.contains( "elements" ) || !obj[ "elements" ].isArray() ) return false;
    auto arr = obj[ "elements" ].toArray();
    for ( auto const &a : arr ) {
        if ( !a.isObject() ) return false;
        auto aObj = a.toObject();
        DataElement el;

        if ( !aObj.contains( "name" ) || aObj[ "name" ].isString() ) return false;
        el.name = aObj[ "name" ].toString();

        if ( !aObj.contains( "info" ) ) return false;
        el.info = aObj[ "info" ].toVariant();

        elements.append( el );
    }

    if ( !obj.contains( "title" ) || !obj[ "title" ].isString() ) return false;
    title = obj[ "title" ].toString();

    return true;
}

const QString &Data::getTitle() const
{
    return title;
}

void Data::setTitle( const QString &newTitle )
{
    title = newTitle;
}
