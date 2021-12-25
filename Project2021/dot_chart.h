#ifndef DOT_CHART_H
#define DOT_CHART_H
#include <vector>
#include "cartesian_chart.h"

class dot_chart: public cartesian_chart
{
private:
    std::vector<point> points;
public:
    dot_chart(const std::string& ="Grafico", const std::string& ="X", const std::string& ="Y");

    void add_point(float, float) override;
    std::vector<std::pair<float,float>> get_points() const override;
    uint get_points_amount() const override;

    float mean_x() const;
    float mean_y() const;
    float variance_x() const;
    float variance_y() const;
    float covariance() const;
};

#endif // DOT_CHART_H
