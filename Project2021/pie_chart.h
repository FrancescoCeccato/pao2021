#ifndef PIE_CHART_H
#define PIE_CHART_H
#include "comparison_chart.h"

class pie_chart : public comparison_chart
{
public:
    pie_chart(const std::string& ="");

    double give_total_sum() const;
    double give_slice_percentage(uint) const;
    std::pair<double, std::string> give_max() const;

    void add_entry(double*,const std::string& = "") override;
    void add_entry(double,const std::string& = "");
    //void remove_entry(uint) override;
};

#endif // PIE_CHART_H
