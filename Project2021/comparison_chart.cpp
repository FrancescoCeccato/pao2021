#include "comparison_chart.h"

comparison_chart::entry::entry(const std::string& title, double* val) : label(title)
{

}

comparison_chart::entry::~entry()
{
    delete[] values;
}

comparison_chart::entry::operator double() const {
    return values[0];
}

double comparison_chart::entry::give_sum() const {
    double sum = 0;
    for(uint i = 0; i<n_values; i++)
        sum += values[i];
    return sum;
}

double comparison_chart::entry::give_value(uint index) const {
    //exception handling?
    return values[index];
}

double comparison_chart::entry::give_percentage(uint index) const {
    //exception handling?
    return 100*values[index] / give_sum();
}

comparison_chart::comparison_chart(uint amt, const std::string& t) : chart(t), values_per_entry(amt) {}

