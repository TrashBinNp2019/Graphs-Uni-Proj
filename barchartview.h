#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include <QObject>
#include "customchartview.h"

class BarChartView : public CustomChartView
{
    Q_OBJECT
public:


    // CustomChartView interface
public:
    void updateDate();
};

#endif // BARCHARTVIEW_H
