#include "data.h"

Data::Data(QObject *)
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
