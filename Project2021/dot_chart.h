#ifndef DOT_CHART_H
#define DOT_CHART_H
#include "cartesian_chart.h"

class dot_chart: public cartesian_chart
{
public:
    dot_chart(const std::string&, const std::string&, const std::string&);
    void add_point(float, float) override;
};

#endif // DOT_CHART_H
