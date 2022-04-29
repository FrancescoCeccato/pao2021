#ifndef STACKED_BAR_CHART_H
#define STACKED_BAR_CHART_H
#include <vector>
#include <string>
#include "bar_chart.h"

class stacked_bar_chart: public bar_chart
{
private:
    std::vector<std::string> categories;
    bool segmented;
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;

public:
    std::vector<std::string> chart_info() const override;
    static std::string description();

    stacked_bar_chart(uint, bool, const std::string& ="",bool=false);
    stacked_bar_chart(const stacked_bar_chart&) = delete;
    void set_categories(const std::vector<std::string>&);
    std::vector<std::string> get_categories() const;
    bool is_segmented() const;
    double max() const;
};

#endif // STACKED_BAR_CHART_H
