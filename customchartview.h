#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H
#include "data.h"

#include <QChart>
#include <QChartView>




class CustomChartView : public QChartView

{




public:


    virtual void updateDate();


    Data *getData() const;
    void setData(Data *newData);

protected:
    Data* data;

};

#endif // CUSTOMCHARTVIEW_H
