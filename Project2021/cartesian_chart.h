#ifndef CARTESIAN_CHART_H
#define CARTESIAN_CHART_H
#include <set>
#include <string>
#include "chart.h"

class cartesian_chart: public chart
{
private:
    struct point
    {
        float x;
        float y;

        bool operator==(const point& p) const;
        bool operator<(const point&p) const;
    };

    std::set<point> points;
    std::string label_x, label_y;

public:
    cartesian_chart(std::string x = "X", std::string y = "Y");

    virtual void add_point() = 0;
};

#endif // CARTESIAN_CHART_H
