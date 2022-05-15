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

std::pair<double,std::string> stacked_bar_chart::max() const{
    if(entries.size() != 0) {
        std::vector<std::pair<double,std::string>> v;
        for(uint i = 0; i<entries.size(); i++)
            v.push_back(std::pair<double,std::string>(entries[i]->give_sum(), entries[i]->give_label()));
        auto max = std::max_element(v.begin(), v.end());
        return std::pair<double,std::string>(max->first,max->second);
    }
    return std::pair<double,std::string>(0,"");
}

std::vector<double> stacked_bar_chart::mean_per_category() const{
    std::vector<double> mean_categ;
    for(uint i=0; i<get_nvalues()&&entries.size()!= 0;++i){
        mean_categ.push_back(give_mean(i));
    }
    return mean_categ;
}

std::vector<std::string> stacked_bar_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    std::vector<std::string> categ = get_categories();
    std::vector<double> mean_categ = mean_per_category();
    for(uint i= 0; i<get_nvalues() && entries.size()!=0;++i){
        info.push_back("La media della categoria " + categ[i] + " è: " + std::to_string(mean_categ[i]));
    }
    info.push_back("L'entrata con il valore più alto è " + max().second + " con un totale di: " + std::to_string(max().first));
    return info;
}

std::string stacked_bar_chart::description(){
    return "Lo stacked bar chart è un grafico a barre che permette di vedere i cambiamenti dei valori delle diverse categorie a seguito di diversi eventi. Può essere considerato un insieme di simple bar chart.";
}
