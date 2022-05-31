#include "piechartview.h"


void PieChartView::update()
{
    series = new QPieSeries();
    QChart* chart = new QChart();
    for(auto p = data->begin() ; p != data->end() ; ++p){
        series->append(p->info.toString() , p->info.toInt());
    }
    chart->addSeries(series);
    customizePie(chart);

    this->setChart(chart);
}

void PieChartView::customizePie(QChart* chart)
{
    series->setLabelsVisible(true);
    for(auto p : series->slices()){
        QString label = p->label();
            label += ", ";
            label += QString::number(p->percentage() * 100, 'f', 1);
            label += "%";
            p->setLabel(label);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Pie Chart");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
}
