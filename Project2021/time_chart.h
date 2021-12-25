#ifndef TIME_CHART_H
#define TIME_CHART_H
#include <set>
#include "cartesian_chart.h"

class time_chart: public cartesian_chart
{
private:
    struct comparator {
      bool operator()(const point& a, const point& b) const {
        return a.y < b.y;
      }
    };
    std::set<point,comparator> points;

public:
    time_chart(const std::string& ="Grafico", const std::string& ="X", const std::string& ="Y");

    void add_point(float, float) override;
    std::vector<std::pair<float,float>> get_points() const override;
    uint get_points_amount() const override;

    float give_balance(float,float) const;
    float give_max() const;
    float give_min() const;
};

#endif // TIME_CHART_H
