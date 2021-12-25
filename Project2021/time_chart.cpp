#include <iostream>
#include <algorithm>
#include "time_chart.h"

time_chart::time_chart(const std::string& title, const std::string& x, const std::string& y): cartesian_chart(title,x,y) {}

void time_chart::add_point(float x, float y){
    auto a = points.insert((point(x,y)));
    if(!a.second)
    {
        std::cout<<"Porcodio!";
        //lancia eccezione?
    }
}

std::vector<std::pair<float,float>> time_chart::get_points() const {
    std::vector<std::pair<float,float>> v;
    for(auto it = points.begin(); it != points.end(); it++)
        v.push_back(std::pair<float,float>(it->x,it->y));
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
    else std::cout << "oof";


    it = std::find_if(
                    points.begin(),points.end(), [b](const point& p) {return p.y == b;}
                    );
    if(it != points.end())
        last = it->y;
    else std::cout << "oof";

    return last-first;
}

float time_chart::give_min() const {
    return points.begin()->y;
}
float time_chart::give_max() const {
    return points.rbegin()->y;
}
