#ifndef STACKED_BAR_CHART_H
#define STACKED_BAR_CHART_H
#include "bar_chart.h"

class stacked_bar_chart: public bar_chart
{
public:
    stacked_bar_chart(uint amt);

    void add_entry(double*, const std::string&) override;
};

#endif // STACKED_BAR_CHART_H
