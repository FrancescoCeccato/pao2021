#include <vector>
#include <algorithm>
#include "pie_chart.h"

pie_chart::pie_chart(const std::string& title): comparison_chart(1,title){}

double pie_chart::give_total_sum() const{
    double sum = 0;
    for(uint i = 0; i<entries.size(); i++)
        sum += entries[i]->give_value(0);
    return sum;
}

double pie_chart::give_slice_percentage(uint index) const{
    auto size = entries.size();
    if(index<size){
        return 100*entries[index]->give_value(0)/give_total_sum();
    }else
        return 0;
}

std::pair<double, std::string> pie_chart::give_max() const{
    std::vector<std::pair<double,std::string>> v;
    for(uint i = 0; i<entries.size(); ++i){
        v.push_back(std::pair<double,std::string>(entries[i]->give_value(0), entries[i]->give_label()));
    }
    auto x = std::max_element(v.begin(), v.end(),
                              [](const std::pair<const double, std::string>& p1, const std::pair<const double, std::string>& p2) {
                                  return p1.first < p2.first; });
    return *x;
}

void pie_chart::add_entry(double* val,const std::string& label) {
    entry* e = new entry(1,val,label);
    entries.push_back(e);
}

void pie_chart::add_entry(double val,const std::string& label) {
    double* d = new double[1] {val};
    entry* e = new entry(1,d,label);
    entries.push_back(e);
}


