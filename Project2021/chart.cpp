#include "chart.h"

chart::chart(const std::string& s) : title(s) {}

std::string chart::get_title() const {
    return title;
}

void chart::set_title(const std::string& s) {
    title = s;
}

