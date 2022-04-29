#include "model.h"
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <polar_chart.h>
#include <dot_chart.h>
#include <time_chart.h>
#include <iostream>

model::model(){}

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

void model::add_entry_comparison(double * val, std::string label, uint index){
    comparison_chart* cc = static_cast<comparison_chart*>(c);
    if(cc->get_entries_size()>index)
        cc->update_entry(index, val, label);
    else{
        cc->add_entry(val,label);
    }
}

void model::add_point(float x, float y){
    cartesian_chart* cc = static_cast<cartesian_chart*>(c);
    cc->add_point(x,y);
}

void model::delete_point(uint index){
    cartesian_chart* cc = static_cast<cartesian_chart*>(c);
    std::vector<std::pair<float, float>> points = cc->get_points();
    float x = points[index].first, y = points[index].second;
    cc->delete_point(x,y);
}

void model::delete_entry_comparison(uint index){
    comparison_chart* cc = static_cast<comparison_chart*>(c);
    if(cc->get_entries_size()>index)
        cc->delete_entry(index);
}

chart* model::get_chart() const{
    return c;
}

std::vector<std::string> model::chart_info(){
    return c->chart_info();
}

void model::set_categories(std::vector<std::string> cat){
    stacked_bar_chart* stbc = static_cast<stacked_bar_chart*>(c);
    stbc->set_categories(cat);
}

void model::set_amt(uint amt){
    comparison_chart* cc = static_cast<comparison_chart*>(c);
    cc->set_amt(amt);
}

std::string model::chart_description(uint sel){
    switch (sel) {
    case 1:
        return simple_bar_chart::description();
    case 2:
        return stacked_bar_chart::description();
    case 3:
        return pie_chart::description();
    case 4:
        return polar_chart::description();
    case 5:
        return time_chart::description();
    case 6:
        return dot_chart::description();
    }
    return "";
}

float model::give_balance(float x1, float x2){
    time_chart* tc = static_cast<time_chart*>(c);
    return tc->give_balance(x1,x2);
}
