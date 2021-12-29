#ifndef STACKED_BAR_CHART_H
#define STACKED_BAR_CHART_H
#include <vector>
#include <string>
#include "bar_chart.h"

class stacked_bar_chart: public bar_chart
{
private:
    std::vector<std::string> categories;
public:
    stacked_bar_chart(uint,const std::string& ="");

    void add_entry(double*, const std::string&) override;
};

#endif // STACKED_BAR_CHART_H
