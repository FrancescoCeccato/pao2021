#ifndef SEGMENTED_BAR_CHART_H
#define SEGMENTED_BAR_CHART_H
#include "bar_chart.h"

class segmented_bar_chart : public bar_chart
{
private:
    static bool check_input(const std::vector<double>& values);
public:
    segmented_bar_chart(uint);

    void add_entry(double*, const std::string&) override;

};

#endif // SEGMENTED_BAR_CHART_H
