#include <math.h>
#include "dot_chart.h"

dot_chart::dot_chart(const std::string& title, const std::string& x, const std::string& y): cartesian_chart(title,x,y) {}

void dot_chart::add_point(float x, float y){
    points.push_back(point(x,y));
}
std::vector<std::pair<float,float>> dot_chart::get_points() const {
    std::vector<std::pair<float,float>> v;
    for(uint i = 0; i<points.size(); i++)
        v.push_back(std::pair<float,float>(points[i].x,points[i].y));
    return v;
}

uint dot_chart::get_points_amount() const {
    return points.size();
}

float dot_chart::mean_x() const {
    if(!points.empty())
    {
        float sum = 0;
        for(uint i = 0; i<points.size(); i++)
            sum += points[i].x;
        return sum/points.size();
    }
    else return 0;
}

float dot_chart::mean_y() const{
    if(!points.empty())
    {
        float sum = 0;
        for(uint i = 0; i<points.size(); i++)
            sum += points[i].y;
        return sum/points.size();
    }
    else return 0;
}

float dot_chart::variance_x() const {
    if(!points.empty())
    {
        float E = mean_x(), sum = 0;
        for(uint i = 0; i<points.size(); i++)
            sum += std::pow(points[i].x - E, 2);
        return sum/points.size();
    }
    else return 0;
}
float dot_chart::variance_y() const {
    if(!points.empty())
    {
        float E = mean_y(), sum = 0;
        for(uint i = 0; i<points.size(); i++)
            sum += std::pow(points[i].y - E, 2);
        return sum/points.size();
    }
    else return 0;
}

float dot_chart::covariance() const {
    if(!points.empty())
    {
        float Ex = mean_x(), Ey = mean_y(), sum = 0;
        for(uint i = 0; i<points.size(); i++)
            sum += (points[i].x - Ex)*(points[i].y - Ey);
        return sum/points.size();
    }
    else return 0;
}
