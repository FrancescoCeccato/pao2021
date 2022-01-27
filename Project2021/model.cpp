#include "model.h"
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <polar_chart.h>
#include <dot_chart.h>
#include <time_chart.h>
#include <iostream>

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

//std::string model::get_title() const {return c->get_title();}

chart* model::get_chart() const{
    return c;
}

std::vector<std::string> model::chart_info(){
    return c->chart_info();
}

/*double model::get_mean() const {
    if(typeid (c) == typeid (simple_bar_chart))
        return static_cast<const simple_bar_chart&>(c).mean();
    else{
        //throw exception
        return 0;
    }
}*/
