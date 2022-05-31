#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include "data.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>


class CustomChartView : public QChartView
{
    Q_OBJECT

public:
    virtual void update() = 0;


    Data *getData() const;
    void setData(Data *newData);

protected:
    Data* data;

};

#endif // CUSTOMCHARTVIEW_H
