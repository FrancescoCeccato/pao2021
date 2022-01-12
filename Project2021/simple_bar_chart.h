#ifndef SIMPLE_BAR_CHART_H
#define SIMPLE_BAR_CHART_H
#include "bar_chart.h"

class simple_bar_chart: public bar_chart
{
public:
    simple_bar_chart(const std::string& = "", bool = false);

    double mean() const;
    double median() const;
    double mode() const;
    double midrange() const;

    void add_entry(double*,const std::string& = "") override;
    void add_entry(double,const std::string& = "");
};

#endif // SIMPLE_BAR_CHART_H
