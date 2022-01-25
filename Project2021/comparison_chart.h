#ifndef COMPARISON_CHART_H
#define COMPARISON_CHART_H
#include <vector>
#include <string>
#include "chart.h"

class comparison_chart: public chart
{
protected:

    class entry
    {
    private:
        std::string label;
        double* values;
        uint n_values;

        double give_sum() const;

    public:
        entry(uint, double*, const std::string& ="");
        ~entry();
        operator double() const;

        double give_value(uint) const;

        std::string give_label() const;
        void set_label(const std::string&);

        std::vector<double> give_values() const;
        std::vector<double> give_percentages() const;
        void set_values(double*);
    };

    std::vector<entry*> entries;
    uint values_per_entry;

    virtual void insert_entry(uint, double*, const std::string& = "", bool = false) = 0;
    void insert_entry_generic(uint, double*, const std::string& = "", bool = false);

public:
    comparison_chart(uint, const std::string&);
    ~comparison_chart();

    void add_entry(double*,const std::string& = "");
    void update_entry(uint,double*, const std::string&);
    void delete_entry(uint);
    std::string give_entry_label(uint) const;
    std::vector<double> give_entry_values(uint) const;
    std::vector<double> give_entry_percentages(uint) const;
};

#endif // COMPARISON_CHART_H
