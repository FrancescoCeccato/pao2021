#include <iostream>
#include <algorithm>
#include "time_chart.h"

time_chart::time_chart(const std::string& title, const std::string& x, const std::string& y): cartesian_chart(title,x,y) {}

void time_chart::add_point(float x, float y){
    auto a = points.insert(point(x,y));
    if(!a.second)
        throw point_already_present();
}

void time_chart::delete_point(float x, float y)
{
    auto result = points.erase(point(x,y));
    if(result == 0)
        throw point_not_found();
}

std::vector<std::pair<float,float>> time_chart::get_points() const {
    std::vector<std::pair<float,float>> v;
    for(auto it = points.begin(); it != points.end(); it++){
        v.push_back(std::pair<float,float>(it->x,it->y));
    }
    std::sort(v.begin(),v.end(),
              [](const std::pair<const float, const float>& p1, const std::pair<const float, const float>& p2) {
                                return p1.first < p2.first; });
    return v;
}

uint time_chart::get_points_amount() const {
    return points.size();
}

float time_chart::give_balance(float a,float b) const {
    float first = 0,last = 0;

    auto it = std::find_if(
                    points.begin(),points.end(), [a](const point& p) {return p.x == a;}
                    );
    if(it != points.end())
        first = it->y;
    else
        throw point_not_found();


    it = std::find_if(
                    points.begin(),points.end(), [b](const point& p) {return p.x == b;}
                    );
    if(it != points.end())
        last = it->y;
    else
        throw point_not_found();

    return last-first;
}

float time_chart::give_min() const {
    if(points.size()!= 0)
        return points.begin()->y;
    else
        return 0;
}

float time_chart::give_max() const {
     if(points.size()!= 0)
         return points.rbegin()->y;
     else
         return 0;
}

std::vector<std::string> time_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    return info;
}

std::string time_chart::description(){
    return "Il time chart è un grafico a linee che permette di osservare il cambiamento di un certo dato nel tempo.";
}
