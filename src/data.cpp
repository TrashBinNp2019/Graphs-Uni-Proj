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

bool Data::operator ==( const Data &d ) const
{
    if ( elements.size() != d.elements.size() ) return false;
    auto it1 = d.elements.begin();
    for ( auto it = elements.begin(); it != elements.end() && it1 != d.elements.end(); it++, it1++  ) {
        if ( *it != *it1 ) return false;
    }

    return  penColor.name() == d.penColor.name() &&
            brushColor.name() == d.brushColor.name() &&
            penWidth == d.penWidth &&
            title == d.title;
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
        obj[ "info" ] = e.info.toInt();

        arr.append( obj );
    }

    QJsonObject obj;
    obj[ "elements" ] = arr;
    obj[ "title" ] = title;
    obj[ "penColor" ] = penColor.name();
    obj[ "brushColor" ] = brushColor.name();
    obj[ "penWidth" ] = penWidth;

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

        if ( !aObj.contains( "name" ) || !aObj[ "name" ].isString() ) return false;
        el.name = aObj[ "name" ].toString();

        if ( !aObj.contains( "info" ) ) return false;
        el.info = aObj[ "info" ].toVariant();

        elements.append( el );
    }

    if ( !obj.contains( "title" ) || !obj[ "title" ].isString() ) return false;
    title = obj[ "title" ].toString();

    if ( !obj.contains( "penColor" ) || !obj[ "penColor" ].isString() ) return false;
    penColor = QColor( obj[ "penColor" ].toString() );

    if ( !obj.contains( "brushColor" ) || !obj[ "brushColor" ].isString() ) return false;
    brushColor = QColor( obj[ "brushColor" ].toString() );

    if ( !obj.contains( "penWidth" ) || !obj[ "penWidth" ].isDouble() ) return false;
    penWidth = obj[ "penWidth" ].toInt();

    return true;
}

const qsizetype Data::getSize() const
{
    return elements.size();
}

const QString &Data::getTitle() const
{
    return title;
}

void Data::setTitle( const QString &newTitle )
{
    title = newTitle;
}

const QColor &Data::getPenColor() const
{
    return penColor;
}

void Data::setPenColor(const QColor &newPenColor)
{
    penColor = newPenColor;
}

const QColor &Data::getBrushColor() const
{
    return brushColor;
}

void Data::setBrushColor(const QColor &newBrushColor)
{
    brushColor = newBrushColor;
}

int Data::getPenWidth() const
{
    return penWidth;
}

void Data::setPenWidth(int newPenWidth)
{
    penWidth = newPenWidth;
}
