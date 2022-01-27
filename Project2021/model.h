#ifndef MODEL_H
#define MODEL_H
#include <chart.h>
#include <vector>

class model
{
private:
    chart* c;
public:
    model(const std::string& = "");
    void add_charts(uint, std::string, uint, bool, bool, std::string, std::string);
    void add_entry_comparison(uint, double*, std::string, uint);
    void delete_entry_comparison(uint);
    void add_point(uint,float, float);
    void delete_point(uint,uint);
    std::vector<std::string> chart_info(uint);
    //std::string get_title() const;
    chart* get_chart()const;
    //double get_mean() const;
};

#endif // MODEL_H
