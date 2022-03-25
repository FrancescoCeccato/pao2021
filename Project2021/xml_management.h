#ifndef XML_MANAGEMENT_H
#define XML_MANAGEMENT_H

#include <QtXml>
#include <QDebug>
#include <chart.h>


class xml_management
{
private:
    QDomDocument chart_xml;
public:
    xml_management();
    void write_xml(chart*);
};

#endif // XML_MANAGEMENT_H
