#include "piechartview.h"


void PieChartView::updateDate()
{
    series = new QPieSeries();
    QChart* chart = new QChart();
    for(auto p = data->begin() ; p != data->end() ; ++p){
        series->append(p->info.toString() , p->info.toInt());
    }
    chart->addSeries(series);
    this->setChart(chart);
}
