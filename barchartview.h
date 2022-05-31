#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include "customchartview.h"

#include <QBarSeries>

class BarChartView: public CustomChartView
{
public:
    BarChartView();
    void updateData();

private:
    QBarSeries *series;
};

#endif // BARCHARTVIEW_H
