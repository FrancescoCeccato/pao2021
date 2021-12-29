#include <cmath>
#include "polar_chart.h"

polar_chart::polar_chart(const std::string& title) : comparison_chart(1, title) {}

double polar_chart::find_max() const
{
    double max = 0;
    for(uint i = 0; i<entries.size(); i++)
    {
        if(*(entries[i]) > max)
            max = *(entries[i]);
    }
    return max;
}

double polar_chart::give_completion_percentage() const
{
    double max = find_max();
    double sum = 0;
    for(uint i = 0; i<entries.size(); i++)
        sum += *(entries[i])/max;
    return sum/entries.size();
}

void polar_chart::add_entry(double* val,const std::string& label) {
    *val = std::round(*val);
    entry* e = new entry(1,val,label);
    entries.push_back(e);
}

void polar_chart::add_entry(double val,const std::string& label) {
    double* d = new double[1] {std::round(val)};
    entry* e = new entry(1,d,label);
    entries.push_back(e);
}
