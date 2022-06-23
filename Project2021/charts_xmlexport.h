#ifndef CHARTS_XMLEXPORT_H
#define CHARTS_XMLEXPORT_H
#include <chart.h>
#include <QString>
#include <QDomDocument>
#include <map>
#include <functional>
#include <typeinfo>
#include <typeindex>

class Charts_XmlExport
{
typedef std::map<uint,void(Charts_XmlExport::*)()> MethodMap;
typedef std::map<std::type_index, uint> TypeMap;

public:
    Charts_XmlExport(chart*, const QString&);
    void exportContent();

private:
    chart* ch;
    QDomDocument doc;
    QDomElement container;

    QString filename;

    MethodMap mmap;
    static TypeMap tmap;

    uint chartType(chart*) const;

    void initiateDocument();
    void writeCartesianChartDocument();
    void writeComparisonChartDocument();
    void writeBarChartDocument();
    void writeStackedBarChartDocument();
    void finalizeDocument();
};

#endif // CHARTS_XMLEXPORT_H
