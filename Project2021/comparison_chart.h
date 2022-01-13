#ifndef COMPARISON_CHART_H
#define COMPARISON_CHART_H
#include <vector>
#include <string>
#include "chart.h"

class comparison_chart: public chart
{
public:
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
        double give_percentage(uint) const;
        std::string give_label() const;
    };
protected:
    std::vector<entry*> entries;
    uint values_per_entry;

public:
    comparison_chart(uint, const std::string&);
    ~comparison_chart();
    entry* get_entry(uint)const;
    uint get_nvalues() const;
    uint get_entries_size() const;
    virtual void add_entry(double*,const std::string& = "") = 0;
<<<<<<< HEAD
    //virtual void update_entry(uint,double*) = 0;
    //virtual void delete_entry(uint) = 0;
    virtual void remove_entry(uint) = 0;
=======
    virtual void update_entry(uint,double*) = 0;
    void delete_entry(uint);
>>>>>>> main
};

#endif // COMPARISON_CHART_H
