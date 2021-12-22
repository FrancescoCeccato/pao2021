#include "bar_chart.h"

bar_chart::bar_chart(uint amt, const std::string& t) : comparison_chart(amt,t) { }

double bar_chart::give_mean(uint value_index) const {
    double sum = 0;
    auto size = entries.size();
    for(uint i = 0; i<size; i++)
        sum += entries[i]->give_value(value_index);
    return sum/size;
}
