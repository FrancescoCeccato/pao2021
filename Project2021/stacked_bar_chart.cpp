#include "stacked_bar_chart.h"
#include <stdexcept>

stacked_bar_chart::stacked_bar_chart(uint amt, bool seg, const std::string& title, bool h): bar_chart(amt,title,h), segmented(seg) {}

void stacked_bar_chart::add_entry(double* val, const std::string& label) {
    entry* e = new entry(values_per_entry,val,label);
    entries.push_back(e);
}

/*void stacked_bar_chart::remove_entry(uint index){
    if(index >= entries.size())
        throw std::out_of_range("Index greater than the number of entries");
    else
        entries.erase(entries.begin()+index);
}*/

void stacked_bar_chart::set_categories(const std::vector<std::string>& categories) {
    this->categories = categories;
}

std::string stacked_bar_chart::get_categories(uint index) const {
    if(index < categories.size()){
         return categories[index];
    }else
        throw std::out_of_range("Index greater than the number of entries");
}

bool stacked_bar_chart::is_segmented() const
{
    return segmented;
}


