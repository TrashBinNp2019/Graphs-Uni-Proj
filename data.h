#ifndef DATA_H
#define DATA_H

#include <QJsonDocument>
#include <QObject>

typedef QVariant InfoSet;

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
    bool fromJson( const QJsonDocument & );

    const QString &getTitle() const;
    void setTitle(const QString &newTitle);

// if needed
//
//signals:
//    void elementsAppended();

private:
    QList< DataElement > elements;
    QString title;
};

#endif // DATA_H
