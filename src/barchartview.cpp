#include "barchartview.h"
#include <QBarSet>
#include <QValueAxis>


BarChartView::BarChartView()
{

}

void BarChartView::update()
{
    series = new QBarSeries();
    QChart *chart = new QChart();
    qreal min = 0;
    qreal max = 0;
    for(auto it = data->begin(); it != data->end(); it++){
        auto q = new QBarSet(it->name);
        auto val = it->info.toDouble();
        if ( val > max ) max = val;
        if ( val < min ) min = val;
        *q << it->info.toDouble();

        q->setBrush( data->getBrushColor() );
        q->setPen( { data->getPenColor(), static_cast<qreal>(data->getPenWidth()) } );

        series->append(q);
    }
    chart->setTitle( data->getTitle() );
    chart->addSeries(series);

    QValueAxis *axis = new QValueAxis();
    axis->setRange( min, max );
    chart->addAxis( axis, Qt::AlignLeft );

    this->setChart(chart);
}
