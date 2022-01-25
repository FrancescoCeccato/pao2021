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
    double sum = 0;
    for(uint i = 0; i<entries.size(); i++)
        sum += *(entries[i])/find_max();
    return sum/entries.size();
}

void polar_chart::insert_entry(uint index, double *val, const std::string &label, bool overwrite) {
    for(uint i = 0; i<values_per_entry; i++)
        val[i] = std::round(val[i]);
    insert_entry_generic(index,val,label,overwrite);
}
