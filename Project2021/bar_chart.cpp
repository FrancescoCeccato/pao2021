#include "bar_chart.h"

bar_chart::bar_chart(uint amt, const std::string& t, bool h) : comparison_chart(amt,t), horizontal(h){ }

double bar_chart::give_mean(uint value_index) const {
    double sum = 0;
    auto size = entries.size();
    if(size != 0){
        for(uint i = 0; i<size; i++)
            sum += entries[i]->give_value(value_index);
        return sum/size;
    }
    return sum;
}

bool bar_chart::is_horizontal() const
{
    return horizontal;
}

void bar_chart::set_horizontal(bool h)
{
    horizontal = h;
}
