#include <chart.h>

chart::chart(const std::string& s) : title(s) {}

std::string chart::get_title() const {
    return title;
}

std::vector<std::string> chart::chart_info() const{
    std::vector<std::string> info;
    info.push_back("Titolo: " + get_title());
    return info;
}
