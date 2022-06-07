#include <QtTest>

#include "../src/data.h"

class TestData : public QObject
{
    Q_OBJECT

public:
    TestData();
    ~TestData();

private slots:
    void test_properties();
    void test_json_io();
    void test_list_read_size();
    void test_list_append();

private:
    Data *data;
};

TestData::TestData()
{
    data = new Data();
    data->setTitle( "test" );
    data->setBrushColor( Qt::white );
    data->setPenColor( Qt::black );
    data->setPenWidth( 10 );

    *data << Data::DataElement( { 5, "fisrt" } );
    *data << Data::DataElement( { 5, "second" } );
}

TestData::~TestData()
{
    delete data;
}

void TestData::test_properties()
{
    QCOMPARE( data->getBrushColor(), QColor( Qt::white ) );
    QCOMPARE( data->getPenColor(), QColor( Qt::black ) );
    QCOMPARE( data->getTitle(), "test" );
    QCOMPARE( data->getPenWidth(), 10 );
}

void TestData::test_json_io()
{
    auto doc = data->toJson();
    Data data1;
    data1.fromJson( doc );

    QCOMPARE( *data, data1 );
}

void TestData::test_list_read_size()
{
    auto size = data->getSize();
    int count = 0;
    for ( auto it = data->begin(); it != data->end(); it++ ) {
        count++;
    }

    QCOMPARE( size, count );
}

void TestData::test_list_append()
{
    Data::DataElement el{ 3, "test" };
    *data << el;

    QCOMPARE( *( --data->end() ), el );
}

QTEST_APPLESS_MAIN(TestData)

#include "tst_main.moc"
