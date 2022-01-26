#ifndef STACKED_BAR_CHART_H
#define STACKED_BAR_CHART_H
#include <vector>
#include <string>
#include "bar_chart.h"

class stacked_bar_chart: public bar_chart
{
private:
    std::vector<std::string> categories;
    bool segmented;
    void insert_entry(uint, double*, const std::string& = "", bool = false) override;

public:
<<<<<<< HEAD
    stacked_bar_chart(uint, bool, const std::string& ="", bool=false);

    void add_entry(double*, const std::string&) override;
    //void remove_entry(uint) override;

    void set_categories(const std::vector<std::string>&);
    std::string get_categories(uint) const;

=======
    stacked_bar_chart(uint, bool, const std::string& ="",bool=false);
    stacked_bar_chart(const stacked_bar_chart&) = delete;


    void set_categories(const std::vector<std::string>&);
    std::vector<std::string> get_categories() const;
>>>>>>> 22
    bool is_segmented() const;
};

#endif // STACKED_BAR_CHART_H
