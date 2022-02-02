#include "chart.h"

chart::chart(const std::string& s) : title(s) {}

std::string chart::get_title() const {
    return title;
}

