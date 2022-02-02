#ifndef CHART_H
#define CHART_H
#include <string>
#include <vector>

typedef unsigned int uint;

class chart
{
private:
    std::string title;
public:
    chart(const std::string&);
    virtual ~chart() = default;
    virtual std::vector<std::string> chart_info() const = 0;
    virtual std::string description() const = 0;

    std::string get_title() const;

};

#endif // CHART_H
