#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include <QObject>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include "customchartview.h"

class PieChartView: public CustomChartView
{
    Q_OBJECT

public:



public:
    void update() override;
private:
    QPieSeries* series;
    void customizePie(QChart* chart);


};

#endif // PIECHARTVIEW_H
