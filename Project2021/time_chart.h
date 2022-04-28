#ifndef TIME_CHART_H
#define TIME_CHART_H
#include <set>
#include "cartesian_chart.h"

class time_chart: public cartesian_chart
{
private:
    struct comparator {
      bool operator()(const point& a, const point& b) const {
        return a.x < b.x;
      }
    };
    std::set<point,comparator> points;

public:
    time_chart(const std::string& ="", const std::string& ="X", const std::string& ="Y");

    void add_point(float, float) override;
    void delete_point(float,float) override;
    std::vector<std::pair<float,float>> get_points() const override;
    uint get_points_amount() const override;

    float give_balance(float,float) const;
    float give_min() const;
    float give_max() const;

    std::vector<std::string> chart_info() const override;
    static std::string description();
};

#endif // TIME_CHART_H
