#include <cmath>
#include "polar_chart.h"
#include <algorithm>
#include <stdexcept>

polar_chart::polar_chart(const std::string& title) : comparison_chart(1, title) {}

double polar_chart::find_max() const
{
    double max = 0;
    for(uint i = 0; i<entries.size(); i++)
    {
        if(*entries[i] > max)
            max = *entries[i];
    }
    return max;
}

double polar_chart::give_completion_percentage() const
{
    double sum = 0;
    for(uint i = 0; i<entries.size(); i++)
        sum += *entries[i]/find_max();
    return sum/entries.size();
}

double polar_chart::midrange() const {
    std::vector<double> v;
    for(uint i = 0; i<entries.size(); i++)
        v.push_back(entries[i]->give_value(0));
    auto pair = std::minmax_element(v.begin(),v.end());
    return (*(pair.second) - *(pair.first));
}

void polar_chart::insert_entry(uint index, double *val, const std::string &label, bool overwrite) {
    for(uint i = 0; i<values_per_entry; i++)
        val[i] = std::round(val[i]);
    insert_entry_generic(index,val,label,overwrite);
}

std::vector<std::string> polar_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    return info;
}

std::string polar_chart::description(){
    return "Il polar chart è un grafico che permette di osservare i diversi parametri di un certo dato, paragonandoli fra loro e analizzando quali parametri influiscono di più e quali di meno.";
}

