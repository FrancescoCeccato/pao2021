#include "stacked_bar_chart.h"

stacked_bar_chart::stacked_bar_chart(uint amt,const std::string& title): bar_chart(amt,title) {}

void stacked_bar_chart::add_entry(double* val,const std::string& label) {
    entry* e = new entry(1,val,label);
    entries.push_back(e);
}


