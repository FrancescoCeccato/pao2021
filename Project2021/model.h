#ifndef MODEL_H
#define MODEL_H
#include <chart.h>

class model
{
private:
    chart* c;
public:
    model(const std::string& = "");
    void add_comparison_charts(uint, std::string, uint, bool, bool);
    void add_cartesian_charts(uint, std::string, std::string, std::string);
    void add_entry_comparison(uint, double*, std::string);
    void add_info(uint);
    std::string get_title() const;
    const chart* get_chart()const;
    //double get_mean() const;
};

#endif // MODEL_H
