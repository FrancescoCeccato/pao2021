#include <algorithm>
#include <map>
#include "simple_bar_chart.h"

simple_bar_chart::simple_bar_chart(const std::string& title, bool h): bar_chart(1,title,h) {}

double simple_bar_chart::mean() const {
    return give_mean(0);
}

double simple_bar_chart::median() const {
    if(entries.size() != 0){
        std::vector<double> v;
        for(uint i = 0; i<entries.size(); i++)
            v.push_back(*(entries[i]));
        auto m = v.begin() + v.size()/2;
        std::nth_element(v.begin(), m, v.end());

        return v[v.size()/2];
    }
    return 0;
}

double simple_bar_chart::mode() const {
    if(entries.size() != 0){
        std::map<double,uint> map;
        for(uint i = 0; i<entries.size(); i++)
            ++map[*(entries[i])];
        auto x = std::max_element(map.begin(), map.end(),
                                         [](const std::pair<const double, uint>& p1, const std::pair<const double, uint>& p2) {
                                             return p1.second < p2.second; });
        return x->first;
    }
    return 0;
}

double simple_bar_chart::midrange() const {
    if(entries.size() != 0) {
        std::vector<double> v;
        for(uint i = 0; i<entries.size(); i++)
            v.push_back(*(entries[i]));
        auto pair = std::minmax_element(v.begin(),v.end());
        return (*(pair.second) - *(pair.first));
    }
    return 0;
}

void simple_bar_chart::insert_entry(uint index, double *val, const std::string &label, bool overwrite) {
    insert_entry_generic(index,val,label,overwrite);
}

std::vector<std::string> simple_bar_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    info.push_back("La media delle entrate di questo grafico è: " + std::to_string(mean()));
    info.push_back("La mediana delle entrate di questo grafico è: " + std::to_string(median()));
    info.push_back("La moda delle entrate di questo grafico è: " + std::to_string(mode()));
    info.push_back("Il midrange delle entrate di questo grafico è: " + std::to_string(midrange()));
    return info;
}

std::string simple_bar_chart::description(){
    return "Il simple bar chart è un grafico a barre che permette di comparare diverse categorie tra loro. Ciò permette di fare anche analisi statistiche tra le diverse categorie.";
}

