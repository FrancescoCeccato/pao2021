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

        bool operator==(const point&) const;
        bool operator<(const point&) const;
        point(float=0, float=0);
    };
    std::string label_x, label_y;

protected:
    std::set<point> points;

public:

    cartesian_chart(const std::string&, const std::string&, const std::string&);

    virtual void add_point(float, float) = 0;
    std::pair<float,float> get_point(uint index) const;
    uint get_points_amount() const;
};

#endif // CARTESIAN_CHART_H
