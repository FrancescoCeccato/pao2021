#include "model.h"
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <polar_chart.h>
#include <dot_chart.h>
#include <time_chart.h>

model::model(const std::string& title) : c(new chart(title)){}

void model::add_charts(uint code, std::string title, uint amt, bool h, bool seg, std::string x, std::string y){
    switch (code) {
    case 1:
        c = new simple_bar_chart(title,h);
        break;
    case 2:
        c = new stacked_bar_chart(amt, seg, title, h);
        break;
    case 3:
        c = new pie_chart(title);
        break;
    case 4:
        c = new polar_chart(title);
        break;
    case 5:
        c = new time_chart(title, x, y);
        break;
    case 6:
        c = new dot_chart(title, x, y);
        break;
    }
}

void model::add_entry_comparison(uint code, double * val, std::string label){
    switch (code) {
    case 1:{
        simple_bar_chart* sbc = static_cast<simple_bar_chart*>(c);
        sbc->add_entry(val,label);
        break;
    }
    {
    case 2:
        stacked_bar_chart* stbc = static_cast<stacked_bar_chart*>(c);
        stbc->add_entry(val,label);
        break;
        }
    {
    case 3:
        pie_chart* pc = static_cast<pie_chart*>(c);
        pc->add_entry(val,label);
        break;
        }
    {
    case 4:
        polar_chart* plc = static_cast<polar_chart*>(c);
        plc->add_entry(val,label);
        break;
        }
    }
}

void model::delete_entries(uint i){
    comparison_chart* cc = static_cast<comparison_chart*>(c);
    cc->delete_entry(i);
}

std::string model::get_title() const {return c->get_title();}

chart* model::get_chart() const{
    return c;
}

/*double model::get_mean() const {
    if(typeid (c) == typeid (simple_bar_chart))
        return static_cast<const simple_bar_chart&>(c).mean();
    else{
        //throw exception
        return 0;
    }
}*/
