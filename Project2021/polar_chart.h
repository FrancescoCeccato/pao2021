#ifndef POLAR_CHART_H
#define POLAR_CHART_H
#include "comparison_chart.h"


class polar_chart: public comparison_chart
{
private:
    double find_max() const;
public:
    polar_chart(const std::string& ="");

    double midrange() const;
    double give_completion_percentage() const;

    void add_entry(double*,const std::string& = "") override;
    void add_entry(double,const std::string& = "");
    void remove_entry(uint) override;
};

#endif // POLAR_CHART_H
