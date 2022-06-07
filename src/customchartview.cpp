#include "customchartview.h"

Data *CustomChartView::getData() const
{
    return data;
}

void CustomChartView::setData(Data *newData)
{
    data = newData;
}
