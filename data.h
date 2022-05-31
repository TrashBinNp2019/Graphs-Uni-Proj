#ifndef DATA_H
#define DATA_H

#include <QJsonDocument>
#include <QObject>

typedef QList< QVariant > InfoSet;

class Data : public QObject
{
    Q_OBJECT

public:
    struct DataElement {
        InfoSet info;
        QString name;
    };
    Data( QObject* = nullptr );

    Data *operator <<(const DataElement &element );

    // read
    QList< Data::DataElement >::iterator begin();
    QList< Data::DataElement >::iterator end();

    QJsonDocument toJson() const;
    void fromJson( const QJsonDocument & );

// if needed
//
//signals:
//    void elementsAppended();

private:
    QList< DataElement > elements;
};

#endif // DATA_H
