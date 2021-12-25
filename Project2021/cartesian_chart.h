#ifndef CARTESIAN_CHART_H
#define CARTESIAN_CHART_H
#include <set>
#include <string>
#include <vector>
#include "chart.h"

class cartesian_chart: public chart
{
protected:
    struct point
    {
        float x;
        float y;

        point(float=0, float=0);
    };
    std::string label_x, label_y;

public:
    cartesian_chart(const std::string&, const std::string&, const std::string&);

    virtual void add_point(float, float) = 0;
    virtual std::vector<std::pair<float,float>> get_points() const = 0;
    virtual uint get_points_amount() const = 0;
};

#endif // CARTESIAN_CHART_H
