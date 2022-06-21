#ifndef BAR_CHART_H
#define BAR_CHART_H
#include <comparison_chart.h>

class bar_chart: public comparison_chart
{
protected:
    bool horizontal;
    double give_mean(uint) const;
public:
    bar_chart(uint, const std::string&, bool);

    bool is_horizontal() const;
    void set_horizontal(bool);
};

#endif // BAR_CHART_H
