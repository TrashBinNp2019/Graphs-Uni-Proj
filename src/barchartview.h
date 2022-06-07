#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include "customchartview.h"

#include <QtCharts/QBarSeries>

class BarChartView: public CustomChartView
{
    Q_OBJECT

public:
    BarChartView();
    void update() override;

private:
    QBarSeries *series;
};

#endif // BARCHARTVIEW_H
