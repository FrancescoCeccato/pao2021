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

void model::add_entry_comparison(uint code, double * val, std::string label, uint index){
    switch (code) {
    case 1:{
        simple_bar_chart* sbc = static_cast<simple_bar_chart*>(c);
        if(sbc->get_entries_size()>index)
            sbc->update_entry(index, val, label);
        else{
            sbc->add_entry(val,label);
        }
        break;
    }
    {
    case 2:
        stacked_bar_chart* stbc = static_cast<stacked_bar_chart*>(c);
        if(stbc->get_entries_size()>index)
            stbc->update_entry(index, val, label);
        else{
            stbc->add_entry(val,label);
        }
        break;
        }
    {
    case 3:
        pie_chart* pc = static_cast<pie_chart*>(c);
        if(pc->get_entries_size()>index)
            pc->update_entry(index, val, label);
        else{
            pc->add_entry(val,label);
        }
        break;
        }
    {
    case 4:
        polar_chart* plc = static_cast<polar_chart*>(c);
        if(plc->get_entries_size()>index)
            plc->update_entry(index, val, label);
        else{
            plc->add_entry(val,label);
        }
        break;
        }
    }
}

void model::add_point(uint code,float x, float y){
    switch (code) {
    case 5:{
        time_chart* tc = static_cast<time_chart*>(c);
        tc->add_point(x,y);
        break;
    }
    {
    case 6:
        dot_chart* dc = static_cast<dot_chart*>(c);
        dc->add_point(x,y);
        break;
    }
    }
}

void model::delete_point(uint code, uint index){
    std::vector<std::pair<float, float>> points;
    switch (code) {
    case 5:{
        time_chart* tc = static_cast<time_chart*>(c);
        points = tc->get_points();
        float x = points[index].first, y = points[index].second;
        tc->delete_point(x,y);
        break;
    }
    {
    case 6:
        dot_chart* dc = static_cast<dot_chart*>(c);
        points = dc->get_points();
        float x = points[index].first, y = points[index].second;
        dc->delete_point(x,y);
        break;
    }
    }
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

std::vector<std::string> model::chart_info(uint code){
    std::vector<std::string> info;
    switch (code) {
    case 1:{
        simple_bar_chart* sbc = static_cast<simple_bar_chart*>(c);
        info.push_back("Titolo: " + sbc->get_title());
        info.push_back("La media delle entrate di questo grafico è: " + std::to_string(sbc->mean()));
        info.push_back("La mediana delle entrate di questo grafico è: " + std::to_string(sbc->median()));
        info.push_back("La moda delle entrate di questo grafico è: " + std::to_string(sbc->mode()));
        info.push_back("Il midrange delle entrate di questo grafico è: " + std::to_string(sbc->midrange()));
        break;
    }
    case 2:{

        break;
    }
    case 3:{

        break;
    }
    case 4:{

        break;
    }
    case 5:{

        break;
    }
    case 6:{

        break;
    }
    }
    return info;
}

/*double model::get_mean() const {
    if(typeid (c) == typeid (simple_bar_chart))
        return static_cast<const simple_bar_chart&>(c).mean();
    else{
        //throw exception
        return 0;
    }
}*/
