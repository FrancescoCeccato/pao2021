#ifndef BAR_CHART_H
#define BAR_CHART_H
#include "comparison_chart.h"

class bar_chart: public comparison_chart
{
protected:
    double give_mean(uint) const;
public:
    bar_chart(uint amt, const std::string&);
};

#endif // BAR_CHART_H
