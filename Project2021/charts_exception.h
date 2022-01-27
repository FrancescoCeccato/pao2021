#ifndef CHARTS_EXCEPTION_H
#define CHARTS_EXCEPTION_H
#include <exception>
#include <sstream>
struct charts_exception: public std::exception
{
public:
    const char* what() const noexcept override;
};

struct point_already_present: public charts_exception
{
    float x,y;

    point_already_present(float,float);
    const char* what() const noexcept override;
};

struct point_not_found: public charts_exception
{
    const char* what() const noexcept override;
};


#endif // CHARTS_EXCEPTION_H
