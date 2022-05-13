#include "charts_xmlimport.h"
#include <QFileInfo>
#include <typeinfo>
#include <typeindex>
#include "pie_chart.h"
#include "polar_chart.h"
#include "simple_bar_chart.h"
#include "stacked_bar_chart.h"
#include "simple_bar_chart.h"
#include "time_chart.h"
#include "dot_chart.h"



Charts_XmlImport::Charts_XmlImport(const QString& s,const QString& f): sourceFolder(s),filename(f) {
        mmap = {
            {0,&Charts_XmlImport::createSimpleBarChart},
            {1,&Charts_XmlImport::createStackedBarChart},
            {2,&Charts_XmlImport::createPieChart},
            {3,&Charts_XmlImport::createPolarChart},
            {4,&Charts_XmlImport::createTimeChart},
            {5,&Charts_XmlImport::createDotChart}             
        };
}

std::pair<uint, chart*> Charts_XmlImport::importContent()
{
   if(!QFileInfo::exists(sourceFolder/*+filename*/))
       throw std::ios_base::failure("Il file non è presente nell'unità.");

   QFile file(sourceFolder/*+filename*/);
   if (!file.open(QIODevice::ReadOnly))
       throw std::ios_base::failure("Non è stato possibile aprire il file.");
   if (!doc.setContent(&file)) {
       file.close();
       throw std::logic_error("File XML non riconosciuto.");
   }
   file.close();

   container = doc.elementsByTagName("chart").at(0).toElement();
   chartTitle = container.attribute("title").toStdString();
   auto index = container.attribute("type").toInt();

   try
   {
        if(mmap.find(index) != mmap.end())
        {
            ptr = (this->*mmap[index]) ();
            return std::pair<uint,chart*>(index,ptr);
        }
        else
            return std::pair<uint,chart*>(-1,nullptr);
   }
   catch(...)
   {
       return std::pair<uint,chart*>(-1,nullptr);
   }
}

chart* Charts_XmlImport::createSimpleBarChart() const
{
    auto horizontal = container.elementsByTagName("horizontal").at(0).toElement().attribute("value").toInt();
    auto entriesContainer = container.elementsByTagName("entries").at(0).toElement();

    simple_bar_chart* ch = new simple_bar_chart(chartTitle,horizontal);
    auto entries = entriesContainer.elementsByTagName("entry");
    for(int i = 0; i<entries.count(); i++)
    {
        auto entry = entries.at(i).toElement();
        auto entryLabel = entry.attribute("label").toStdString();
        auto values = entry.elementsByTagName("value");
        double* arr = new double[1];
        arr[0] = values.at(0).toElement().attribute("val").toDouble();

        ch->add_entry(arr,entryLabel);
    }
    return ch;
}

chart* Charts_XmlImport::createStackedBarChart() const
{
    auto horizontal = container.elementsByTagName("horizontal").at(0).toElement().attribute("value").toInt();
    auto segmented = container.elementsByTagName("segmented").at(0).toElement().attribute("value").toInt();

    auto entriesContainer = container.elementsByTagName("entries").at(0).toElement();
    auto nvalues = entriesContainer.attribute("nvalues").toInt();

    stacked_bar_chart* ch = new stacked_bar_chart(nvalues,segmented,chartTitle,horizontal);
    auto entries = entriesContainer.elementsByTagName("entry");
    for(int i = 0; i<entries.count(); i++)
    {
        auto entry = entries.at(i).toElement();
        auto entryLabel = entry.attribute("label").toStdString();
        auto values = entry.elementsByTagName("value");
        double* arr = new double[nvalues];
        for(int i = 0; i<nvalues; i++)
            arr[i] = values.at(i).toElement().attribute("val").toDouble();

        ch->add_entry(arr,entryLabel);
    }

    std::vector<std::string> categoriesVector;
    auto categoriesContainer = container.elementsByTagName("categories").at(0).toElement();
    auto categories = categoriesContainer.elementsByTagName("category");
    for(int i = 0; i<nvalues; i++)
        categoriesVector.push_back(categories.at(i).toElement().attribute("text").toStdString());

    ch->set_categories(categoriesVector);
    return ch;
}

chart* Charts_XmlImport::createPieChart() const
{
    auto entriesContainer = container.elementsByTagName("entries").at(0).toElement();

    pie_chart* ch = new pie_chart(chartTitle);
    auto entries = entriesContainer.elementsByTagName("entry");
    for(int i = 0; i<entries.count(); i++)
    {
        auto entry = entries.at(i).toElement();
        auto entryLabel = entry.attribute("label").toStdString();
        auto values = entry.elementsByTagName("value");
        double* arr = new double[1];
        arr[0] = values.at(0).toElement().attribute("val").toDouble();

        ch->add_entry(arr,entryLabel);
    }
    return ch;
}

chart* Charts_XmlImport::createPolarChart() const
{
    auto entriesContainer = container.elementsByTagName("entries").at(0).toElement();

    polar_chart* ch = new polar_chart(chartTitle);
    auto entries = entriesContainer.elementsByTagName("entry");
    for(int i = 0; i<entries.count(); i++)
    {
        auto entry = entries.at(i).toElement();
        auto entryLabel = entry.attribute("label").toStdString();
        auto values = entry.elementsByTagName("value");
        double* arr = new double[1];
        arr[0] = values.at(0).toElement().attribute("val").toDouble();

        ch->add_entry(arr,entryLabel);
    }
    return ch;
}

chart* Charts_XmlImport::createTimeChart() const
{
    auto ptsContainer = container.elementsByTagName("points").at(0).toElement();
    auto pts = ptsContainer.elementsByTagName("point");

    auto xaxis = container.elementsByTagName("xaxis").at(0).toElement().attribute("label").toStdString();
    auto yaxis = container.elementsByTagName("yaxis").at(0).toElement().attribute("label").toStdString();

    time_chart* ch = new time_chart(chartTitle,xaxis,yaxis);
    try
    {
        for(int i = 0; i<pts.count(); i++)
            ch->add_point(pts.at(i).toElement().attribute("x").toFloat(),
                          pts.at(i).toElement().attribute("y").toFloat());
    }
    catch(...)
    {
        delete ch;
        throw;
    }
    return ch;
}

chart* Charts_XmlImport::createDotChart() const
{
    auto ptsContainer = container.elementsByTagName("points").at(0).toElement();
    auto pts = ptsContainer.elementsByTagName("point");

    auto xaxis = container.elementsByTagName("xaxis").at(0).toElement().attribute("label").toStdString();
    auto yaxis = container.elementsByTagName("yaxis").at(0).toElement().attribute("label").toStdString();

    dot_chart* ch = new dot_chart(chartTitle,xaxis,yaxis);
    try
    {
        for(int i = 0; i<pts.count(); i++)
            ch->add_point(pts.at(i).toElement().attribute("x").toFloat(),
                          pts.at(i).toElement().attribute("y").toFloat());
    }
    catch(...)
    {
        delete ch;
        throw;
    }
    return ch;
}

