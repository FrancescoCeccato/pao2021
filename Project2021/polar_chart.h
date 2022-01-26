#ifndef POLAR_CHART_H
#define POLAR_CHART_H
#include "comparison_chart.h"


class polar_chart: public comparison_chart
{
private:
    double find_max() const;
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;

public:
    polar_chart(const std::string& ="");
    polar_chart(const polar_chart&) = delete;

    double midrange() const;
    double give_completion_percentage() const;
<<<<<<< HEAD

    void add_entry(double*,const std::string& = "") override;
    void add_entry(double,const std::string& = "");
    //void remove_entry(uint) override;
=======
>>>>>>> 22
};

#endif // POLAR_CHART_H
