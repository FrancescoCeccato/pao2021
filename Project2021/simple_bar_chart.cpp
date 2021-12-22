#include <algorithm>
#include <map>
#include "simple_bar_chart.h"

simple_bar_chart::simple_bar_chart(const std::string& title): bar_chart(1,title) {}

double simple_bar_chart::mean() const {
    return give_mean(0);
}

double simple_bar_chart::median() const {
    std::vector<double> v;
    for(uint i = 0; i<entries.size(); i++)
        v.push_back(*(entries[i]));
    auto m = v.begin() + v.size()/2;
    std::nth_element(v.begin(), m, v.end());

    return v[v.size()/2];
}

double simple_bar_chart::mode() const {
    std::map<double,uint> map;
    for(uint i = 0; i<entries.size(); i++)
        ++map[*(entries[i])];
    auto x = std::max_element(map.begin(), map.end(),
                                     [](const std::pair<const double, uint>& p1, const std::pair<const double, uint>& p2) {
                                         return p1.second < p2.second; });
    return x->first;
}

double simple_bar_chart::midrange() const {
    std::vector<double> v;
    for(uint i = 0; i<entries.size(); i++)
        v.push_back(*(entries[i]));
    auto pair = std::minmax(v.begin(),v.end());
    return (pair.second - pair.first);
}
