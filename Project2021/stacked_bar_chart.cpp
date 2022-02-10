#include "stacked_bar_chart.h"
#include <stdexcept>

stacked_bar_chart::stacked_bar_chart(uint amt, bool seg, const std::string& title, bool h): bar_chart(amt,title,h), segmented(seg) {}

void stacked_bar_chart::set_categories(const std::vector<std::string>& categories) {
    this->categories = categories;
}

std::string stacked_bar_chart::get_categories(uint index) const {
    if(index < categories.size()){
         return categories[index];
    }else
        throw std::out_of_range("Index greater than the number of entries");
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

std::string stacked_bar_chart::description(){
    return "Lo stacked bar chart è un grafico a barre che permette di vedere i cambiamenti dei valori delle diverse categorie a seguito di diversi eventi. Può essere considerato un insieme di simple bar chart.";
}
