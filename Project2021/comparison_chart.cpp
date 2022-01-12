#include "comparison_chart.h"

comparison_chart::entry::entry(uint num, double* val,const std::string& title) : label(title), values(val), n_values(num) {}

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
    if(index<n_values)
        return values[index];
    else return 0;
}

std::string comparison_chart::entry::give_label() const {
    return label;
}

double comparison_chart::entry::give_percentage(uint index) const {
    if(index<n_values)
        return 100*values[index] / give_sum();
    else return 0;
}

comparison_chart::comparison_chart(uint amt, const std::string& t) : chart(t), values_per_entry(amt) {}

comparison_chart::~comparison_chart() {
    for(uint i = 0; i<entries.size(); i++)
        delete entries[i];
}

void comparison_chart::update_entry(uint index, double *values) {
    auto string = entries[index]->give_label();
    delete entries[index];
    entries[index] =
}

void comparison_chart::delete_entry(uint index) {
    delete entries[index];
    entries.erase(entries.begin()+index);
}
