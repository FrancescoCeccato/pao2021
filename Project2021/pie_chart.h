#ifndef PIE_CHART_H
#define PIE_CHART_H
#include <comparison_chart.h>

class pie_chart : public comparison_chart
{
private:
    double give_total_sum() const;
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;
public:
    pie_chart(const std::string& ="");

    double give_slice_percentage(uint) const;
    std::pair<double, std::string> give_max() const;

    std::vector<std::string> chart_info() const override;
    static std::string description();
};

#endif // PIE_CHART_H
