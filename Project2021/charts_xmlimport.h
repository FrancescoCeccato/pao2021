#ifndef CHARTS_XMLIMPORT_H
#define CHARTS_XMLIMPORT_H
#include <chart.h>
#include <QDomDocument>
#include <QString>
#include <string>
#include <map>

class Charts_XmlImport
{
private:
    typedef chart*(Charts_XmlImport::*ConstMethod)() const;
    typedef std::map<uint,ConstMethod> MethodMap;

    QString filename;

    QDomDocument doc;
    QDomElement container;
    std::string chartTitle;
    chart* ptr;

    chart* createSimpleBarChart() const;
    chart* createStackedBarChart() const;
    chart* createPieChart() const;
    chart* createPolarChart() const;
    chart* createTimeChart() const;
    chart* createDotChart() const;

    MethodMap mmap;

public:
    Charts_XmlImport(const QString&);

    std::pair<uint, chart*> importContent();
};




#endif // CHARTS_XMLIMPORT_H
