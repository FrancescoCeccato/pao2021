#include <algorithm>
#include "cartesian_chart.h"

bool cartesian_chart::point::operator<(const point& p) const {
    return y < p.y;
}

bool cartesian_chart::point::operator==(const point& p) const {
    return y == p.y && x == p.x;
}

cartesian_chart::point::point(float px,float py) : x(px), y(py) {}

cartesian_chart::cartesian_chart(const std::string& title, const std::string& x, const std::string& y) : chart(title), label_x(x), label_y(y) {}

std::vector<std::pair<float,float>> cartesian_chart::get_point(uint i) const {
    std::vector<std::pair<float,float>> v;
    std::for_each(points.begin(),points.end(), )
}
uint cartesian_chart::get_points_amount() const {
    return points.size();
}
