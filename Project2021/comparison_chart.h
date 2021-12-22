#ifndef COMPARISON_CHART_H
#define COMPARISON_CHART_H
#include <vector>
#include <string>
#include "chart.h"

class comparison_chart: public chart
{
private:

    class entry
    {
    private:
        std::string label;
        double* values;
        uint n_values;

        double give_sum() const;
    public:
        entry(const std::string&, double* = nullptr);
        ~entry();
        operator double() const;
        double give_value(uint) const;
        double give_percentage(uint) const;
    };

protected:

    std::vector<entry*> entries;
    uint values_per_entry;

public:
    comparison_chart(uint, const std::string&);

    virtual void add_entry(double*,const std::string& = "") = 0;
};

#endif // COMPARISON_CHART_H
