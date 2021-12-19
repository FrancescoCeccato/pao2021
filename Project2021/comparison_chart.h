#ifndef COMPARISON_CHART_H
#define COMPARISON_CHART_H
#include <vector>
#include <string>
#include "chart.h"

#define unsigned short uint

class comparison_chart: public chart
{
private:
    class entry
    {
    private:
        std::string label;
        std::vector<double> values;

        double sum_values() const;
    public:
        entry();
        double give_percentage(uint vindex) const;
    };

    std::vector<entry> entries;
    uint entries_amt;

public:
    comparison_chart();

    virtual void addEntry(std::string title,std::vector<double> values);
};

#endif // COMPARISON_CHART_H
