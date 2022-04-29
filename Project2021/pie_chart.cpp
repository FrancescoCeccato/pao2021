#include <vector>
#include <algorithm>
#include <stdexcept>
#include "pie_chart.h"
#include "cmath"

pie_chart::pie_chart(const std::string& title): comparison_chart(1,title){}

double pie_chart::give_total_sum() const {
    double sum = 0;
    for(uint i = 0; i<entries.size(); i++)
        sum += *entries[i];
    return sum;
}

double pie_chart::give_slice_percentage(uint index) const {
    auto size = entries.size();
    if(index<size){
        return 100*(*entries[index])/give_total_sum();
    } else
        return 0;
}

std::pair<double, std::string> pie_chart::give_max() const {
    std::pair<double,std::string> x;
    if(entries.size() != 0){
        std::vector<std::pair<double,std::string>> v;
        for(uint i = 0; i<entries.size(); ++i){
            v.push_back(std::pair<double,std::string>(give_slice_percentage(i), entries[i]->give_label()));
        }
        auto x = std::max_element(v.begin(), v.end(),
                                  [](const std::pair<const double, std::string>& p1, const std::pair<const double, std::string>& p2) {
                                      return p1.first < p2.first; });
        return *x;
    }
    return x;
}

void pie_chart::insert_entry(uint index, double *val, const std::string &label, bool overwrite) {
    insert_entry_generic(index,val,label,overwrite);
}

std::vector<std::string> pie_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    info.push_back("L'entrata con il valore piu alto è " + give_max().second + ": " + std::to_string(give_max().first) + "%");
    return info;
}

std::string pie_chart::description(){
    return "Il pie chart è un grafico a torta che permette di osservare in quale percentuale le diverse categorie influenzano il totale.";
}



