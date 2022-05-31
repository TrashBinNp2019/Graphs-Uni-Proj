#include "barchartview.h"
#include <QBarSet>


BarChartView::BarChartView()
{

}

void BarChartView::updateData()
{
    series = new QBarSeries();
    QChart *chart = new QChart();
    for(auto it = data->begin(); it != data->end(); it++){
        auto q = new QBarSet(it->name);
        *q << it->info.toDouble();
        series->append(q);
    }
    chart->addSeries(series);
    this->setChart(chart);
}
