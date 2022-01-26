#ifndef SIMPLE_BAR_CHART_H
#define SIMPLE_BAR_CHART_H
#include "bar_chart.h"

class simple_bar_chart: public bar_chart
{
private:
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;
public:
    simple_bar_chart(const std::string& = "", bool = false);
    simple_bar_chart(const simple_bar_chart&) = delete;

    double mean() const;
    double median() const;
    double mode() const;
    double midrange() const;
<<<<<<< HEAD

    void add_entry(double*,const std::string& = "") override;
    void add_entry(double,const std::string& = "");
    //void remove_entry(uint) override;
=======
>>>>>>> 22
};

#endif // SIMPLE_BAR_CHART_H
