#include "stacked_bar_chart.h"
#include "algorithm"
#include <stdexcept>

stacked_bar_chart::stacked_bar_chart(uint amt, bool seg, const std::string& title, bool h): bar_chart(amt,title,h), segmented(seg) {}

void stacked_bar_chart::set_categories(const std::vector<std::string> & categories){
    this->categories = categories;
}

std::vector<std::string> stacked_bar_chart::get_categories() const {
    return categories;
}

bool stacked_bar_chart::is_segmented() const {
    return segmented;
}

void stacked_bar_chart::insert_entry(uint index, double *val, const std::string &label, bool overwrite) {
    insert_entry_generic(index,val,label,overwrite);
}

std::vector<std::string> stacked_bar_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    return info;
}

double stacked_bar_chart::max() const{
    if(entries.size() != 0) {
        std::vector<double> v;
        for(uint i = 0; i<entries.size(); i++)
            v.push_back(entries[i]->give_sum());
        return *(std::max_element(v.begin(), v.end()));
    }
    return 0;
}

std::string stacked_bar_chart::description(){
    return "Lo stacked bar chart è un grafico a barre che permette di vedere i cambiamenti dei valori delle diverse categorie a seguito di diversi eventi. Può essere considerato un insieme di simple bar chart.";
}
