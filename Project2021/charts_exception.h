#ifndef CHARTS_EXCEPTION_H
#define CHARTS_EXCEPTION_H
#include <exception>

struct charts_exception: public std::exception
{
    const char* what() const noexcept override;
};

struct point_already_present: public charts_exception
{
    const char* what() const noexcept override;
};

struct point_not_found: public charts_exception
{
    const char* what() const noexcept override;
};

struct chart_not_valid: public charts_exception
{
    const char* what() const noexcept override;
};

struct no_chart_selected: public charts_exception
{
    const char* what() const noexcept override;
};


#endif // CHARTS_EXCEPTION_H
