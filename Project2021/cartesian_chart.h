#ifndef CARTESIAN_CHART_H
#define CARTESIAN_CHART_H
#include <set>
#include <string>
#include <vector>
#include "charts_exception.h"
#include "chart.h"

class cartesian_chart: public chart
{
protected:
    struct point
    {
        float x;
        float y;

        point(float=0, float=0);
        bool operator==(const point&) const;
    };
    std::string label_x, label_y;

public:
    cartesian_chart(const std::string&, const std::string&, const std::string&);

    virtual void add_point(float, float) = 0;
    virtual void delete_point(float,float) = 0;
    virtual std::vector<std::pair<float,float>> get_points() const = 0;
    virtual uint get_points_amount() const = 0;

    std::string get_label_x() const;
    std::string get_label_y() const;
};

#endif // CARTESIAN_CHART_H
