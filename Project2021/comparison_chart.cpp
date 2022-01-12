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

comparison_chart::entry* comparison_chart::get_entry(uint index) const{
    if(index < entries.size())
        return entries[index];
    else{
        //throw exception
    }
}

uint comparison_chart::get_entries_size() const{
    return entries.size();
}

uint comparison_chart::get_nvalues() const{
    return values_per_entry;
}

comparison_chart::comparison_chart(uint amt, const std::string& t) : chart(t), values_per_entry(amt) {}

comparison_chart::~comparison_chart() {
    for(auto it = entries.begin(); it != entries.end(); ++it)
        delete *it;
}
