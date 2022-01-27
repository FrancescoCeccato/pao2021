#ifndef PIE_CHART_H
#define PIE_CHART_H
#include "comparison_chart.h"

class pie_chart : public comparison_chart
{
private:
    double give_total_sum() const;
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;
public:
    pie_chart(const std::string& ="");
    pie_chart(const pie_chart&) = delete;
    std::vector<std::string> chart_info() const override;


    double give_slice_percentage(uint) const;
    std::pair<double, std::string> give_max() const;
};

#endif // PIE_CHART_H
