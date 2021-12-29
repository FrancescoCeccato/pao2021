#ifndef SEGMENTED_BAR_CHART_H
#define SEGMENTED_BAR_CHART_H
#include "stacked_bar_chart.h"

class segmented_bar_chart : public stacked_bar_chart
{
private:
    static bool check_input(double*,uint);
public:
    segmented_bar_chart(uint,const std::string& ="");

    void add_entry(double*, const std::string&) override;
};

#endif // SEGMENTED_BAR_CHART_H
