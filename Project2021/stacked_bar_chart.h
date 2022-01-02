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

public:
    stacked_bar_chart(uint, bool, const std::string& ="",bool=false);

    void add_entry(double*, const std::string&) override;

    void set_categories(const std::vector<std::string>&);
    std::vector<std::string> get_categories() const;

    bool is_segmented() const;

};

#endif // STACKED_BAR_CHART_H
