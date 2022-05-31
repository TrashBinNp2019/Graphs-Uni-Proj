#ifndef DATA_H
#define DATA_H

#include <QColor>
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
    const QColor &getPenColor() const;
    void setPenColor(const QColor &newPenColor);
    const QColor &getBrushColor() const;
    void setBrushColor(const QColor &newBrushColor);
    int getPenWidth() const;
    void setPenWidth(int newPenWidth);

private:
    QList< DataElement > elements;
    QString title;
    QColor penColor;
    QColor brushColor;
    int penWidth;
};

#endif // DATA_H
