#ifndef SIMPLE_BAR_CHART_H
#define SIMPLE_BAR_CHART_H
#include <bar_chart.h>

class simple_bar_chart: public bar_chart
{
private:
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;
public:
    simple_bar_chart(const std::string& = "", bool = false);

    double mean() const;
    double median() const;
    double mode() const;
    double midrange() const;
    std::vector<std::string> chart_info() const override;
    static std::string description();
    double max() const;
};

#endif // SIMPLE_BAR_CHART_H
