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

double polar_chart::midrange() const {
    std::vector<double> v;
    for(uint i = 0; i<entries.size(); i++)
        v.push_back(entries[i]->give_value(0));
    auto pair = std::minmax_element(v.begin(),v.end());
    return (*(pair.second) - *(pair.first));
}

void polar_chart::add_entry(double* val,const std::string& label) {
    *val = std::round(*val);
    entry* e = new entry(1,val,label);
    entries.push_back(e);
}

void polar_chart::add_entry(double val,const std::string& label) {
    double* d = new double[1] {val};
    add_entry(d,label);
}

<<<<<<< HEAD
void polar_chart::remove_entry(uint index){
    if(index >= entries.size())
        throw std::out_of_range("Index greater than the number of entries");
    else
        entries.erase(entries.begin()+index);
}
=======
>>>>>>> main
