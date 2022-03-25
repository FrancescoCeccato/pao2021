#include "comparison_chart.h"
#include "iostream"

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

void comparison_chart::entry::set_label(const std::string &l) {
    label = l;
}

std::vector<double> comparison_chart::entry::give_values() const {
    std::vector<double> output;
    for(uint i = 0; i<n_values; i++)
        output.push_back(values[i]);
    return output;
}

void comparison_chart::entry::set_values(double *v) {
    delete[] values;
    values = v;
}

std::vector<double> comparison_chart::entry::give_percentages() const {
    double sum = give_sum();
    std::vector<double> output;
    for(uint i = 0; i<n_values; i++)
        output.push_back(100*values[i]/sum);
    return output;
}

uint comparison_chart::get_entries_size() const{
    return entries.size();
}

uint comparison_chart::get_nvalues() const{
    return values_per_entry;
}

comparison_chart::comparison_chart(uint amt, const std::string& t) : chart(t), values_per_entry(amt) {}

void comparison_chart::add_entry(double* values, const std::string& title) {
    insert_entry(entries.size(),values,title,false);
}

void comparison_chart::insert_entry_generic(uint index, double *values, const std::string &title, bool overwrite) {
    if(overwrite){
        auto e = entries[index];
        e.set_values(values);
        e.set_label(title);
    }
    else {
        entry e(values_per_entry,values,title);
        entries.insert(entries.begin()+index,e);
    }
}

void comparison_chart::update_entry(uint index, double *values, const std::string& title) {
    insert_entry(index,values,title,true);
}

void comparison_chart::delete_entry(uint index) {
    if(index<entries.size()){
        entries.erase(entries.begin()+index);
    }
}


std::string comparison_chart::give_entry_label(uint index) const {
    return entries[index].give_label();
}

std::vector<double> comparison_chart::give_entry_values(uint index) const{
    return entries[index].give_values();
}

std::vector<double> comparison_chart::give_entry_percentages(uint index) const {
    return entries[index].give_percentages();
}
