#ifndef CHART_H
#define CHART_H
#include <string>

class chart
{
private:
    std::string title;
public:
    chart(const std::string&);
    virtual ~chart() = default;

    std::string get_title() const;
};

#endif // CHART_H
