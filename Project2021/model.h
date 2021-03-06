#ifndef MODEL_H
#define MODEL_H
#include <chart.h>
#include <vector>

class model
{
private:
    chart* c;
public:
    model();
    void add_charts(uint, std::string, uint, bool, bool, std::string, std::string);
    void add_entry_comparison(double*, std::string, uint);
    void delete_entry_comparison(uint);
    void set_categories(std::vector<std::string>);
    void set_amt(uint);
    void add_point(float, float);
    void delete_point(uint);
    std::vector<std::string> chart_info();
    static std::string chart_description(uint);
    chart* get_chart()const;
    void set_chart(chart*);
    float give_balance(float, float);
};

#endif // MODEL_H
