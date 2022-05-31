#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include "customchartview.h"

#include <QtCharts/QBarSeries>

class BarChartView: public CustomChartView
{
    Q_OBJECT

public:
    BarChartView();
    void updateData() override;

private:
    QBarSeries *series;
};

#endif // BARCHARTVIEW_H
