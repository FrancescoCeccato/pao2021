#include "stacked_bar_chart.h"

stacked_bar_chart::stacked_bar_chart(uint amt, bool seg, const std::string& title, bool h): bar_chart(amt,title,h), segmented(seg) {}

void stacked_bar_chart::set_categories(const std::vector<std::string>& categories) {
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
