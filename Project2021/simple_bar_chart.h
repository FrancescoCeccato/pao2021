#ifndef SIMPLE_BAR_CHART_H
#define SIMPLE_BAR_CHART_H
#include "bar_chart.h"

class simple_bar_chart: public bar_chart
{
private:
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;
public:
    simple_bar_chart(const std::string& = "", bool = false);
    simple_bar_chart(const simple_bar_chart&) = delete;
    std::vector<std::string> chart_info() const override;
    std::string description() const override;

    double mean() const;
    double median() const;
    double mode() const;
    double midrange() const;
};

#endif // SIMPLE_BAR_CHART_H
