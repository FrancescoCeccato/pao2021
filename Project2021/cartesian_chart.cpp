#include <algorithm>
#include "cartesian_chart.h"

cartesian_chart::point::point(float px,float py) : x(px), y(py) {}

cartesian_chart::cartesian_chart(const std::string& title, const std::string& x, const std::string& y) : chart(title), label_x(x), label_y(y) {}

