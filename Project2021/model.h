#ifndef MODEL_H
#define MODEL_H
#include <chart.h>

class model
{
private:
    chart* c;
public:
    model(const std::string& = "");
    void add_charts(uint, std::string, uint, bool, bool, std::string, std::string);
    void add_entry_comparison(uint, double*, std::string);
    void delete_entries(uint);
    void add_info(uint);
    std::string get_title() const;
    chart* get_chart()const;
    //double get_mean() const;
};

#endif // MODEL_H
