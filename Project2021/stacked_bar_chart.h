#ifndef STACKED_BAR_CHART_H
#define STACKED_BAR_CHART_H
#include <bar_chart.h>

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
    void set_categories(const std::vector<std::string>&);
    std::vector<std::string> get_categories() const;

    bool is_segmented() const;
    std::pair<double,std::string> max() const;
    std::vector<double> mean_per_category() const;
};

#endif // STACKED_BAR_CHART_H
