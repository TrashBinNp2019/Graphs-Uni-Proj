#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include <QObject>
#include <QPieSeries>
#include <QChart>
#include "customchartview.h"

class PieChartView: public CustomChartView
{
    Q_OBJECT
public:



public:
    void updateDate();
private:
    QPieSeries* series;
    void customizePie(QChart* chart);


};

#endif // PIECHARTVIEW_H
