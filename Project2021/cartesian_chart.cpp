#include <algorithm>
#include "cartesian_chart.h"

cartesian_chart::point::point(float px,float py) : x(px), y(py) {}

bool cartesian_chart::point::operator==(const point& p) const {
    return x == p.x && y == p.y;
}

cartesian_chart::cartesian_chart(const std::string& title, const std::string& x, const std::string& y) : chart(title), label_x(x), label_y(y) {}

std::string cartesian_chart::get_label_x() const {
    return label_x;
}

std::string cartesian_chart::get_label_y() const {
    return label_y;
}
