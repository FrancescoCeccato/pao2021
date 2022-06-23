#include <charts_xmlexport.h>
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <polar_chart.h>
#include <time_chart.h>
#include <dot_chart.h>
#include <QSaveFile>

Charts_XmlExport::Charts_XmlExport(chart* c, const QString& f) : ch(c), filename(f) {
    mmap = {
        {0,&Charts_XmlExport::writeBarChartDocument},
        {1,&Charts_XmlExport::writeStackedBarChartDocument},
        {2,&Charts_XmlExport::writeComparisonChartDocument},
        {3,&Charts_XmlExport::writeComparisonChartDocument},
        {4,&Charts_XmlExport::writeCartesianChartDocument},
        {5,&Charts_XmlExport::writeCartesianChartDocument}
    };
}

void Charts_XmlExport::exportContent() {
    initiateDocument();
    (this->*mmap[tmap[typeid(*ch)]]) ();
    finalizeDocument();

    QSaveFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(qPrintable(doc.toString()));
    file.commit();
}

void Charts_XmlExport::initiateDocument() {
    container = doc.createElement("chart");
    container.setAttribute("title",QString::fromStdString(ch->get_title()));
    container.setAttribute("type",tmap[typeid(*ch)]);
}

void Charts_XmlExport::writeBarChartDocument()
{
    writeComparisonChartDocument();

    auto bc = static_cast<bar_chart*>(ch);
    auto horizontal = doc.createElement("horizontal");
    horizontal.setAttribute("value",bc->is_horizontal());
    container.appendChild(horizontal);
}

void Charts_XmlExport::writeStackedBarChartDocument()
{
    writeBarChartDocument();

    auto bc = static_cast<stacked_bar_chart*>(ch);

    auto segmented = doc.createElement("segmented");
    segmented.setAttribute("value",bc->is_segmented());

    auto categories = doc.createElement("categories");
    QDomElement category;
    auto vec = bc->get_categories();
    for(uint i = 0; i<vec.size(); i++)
    {
        category = doc.createElement("category");
        category.setAttribute("text",QString::fromStdString(vec[i]));
        categories.appendChild(category);
    }
    container.appendChild(segmented);
    container.appendChild(categories);
}

void Charts_XmlExport::writeCartesianChartDocument() {
    auto cc = static_cast<cartesian_chart*>(ch);

    auto pts = cc->get_points();
    auto amt = cc->get_points_amount();

    auto xaxis = doc.createElement("xaxis");
    xaxis.setAttribute("label",QString::fromStdString(cc->get_label_x()));

    auto yaxis = doc.createElement("yaxis");
    yaxis.setAttribute("label",QString::fromStdString(cc->get_label_y()));

    auto points = doc.createElement("points");
    points.setAttribute("amount",amt);

    container.appendChild(xaxis);
    container.appendChild(yaxis);

    QDomElement point;
    for(uint i = 0; i<amt; i++)
    {
        point = doc.createElement("point");
        point.setAttribute("x",pts[i].first);
        point.setAttribute("y",pts[i].second);
        points.appendChild(point);
    }
    container.appendChild(points);
}

void Charts_XmlExport::writeComparisonChartDocument() {
    auto cc = static_cast<comparison_chart*>(ch);

    auto nvalues = cc->get_nvalues();
    auto size = cc->get_entries_size();

    auto entries = doc.createElement("entries");
    entries.setAttribute("nvalues",nvalues);

    QString str;
    std::vector<double> vec;
    for(uint i = 0; i<size; i++)
    {
        str = QString::fromStdString(cc->give_entry_label(i));
        vec = cc->give_entry_values(i);

        auto e = doc.createElement("entry");
        QDomElement val;
        e.setAttribute("index",i);
        e.setAttribute("label",str);
        for(uint j = 0; j<nvalues; j++)
        {
            val = doc.createElement("value");
            val.setAttribute("val",vec[j]);
            e.appendChild(val);
        }
        entries.appendChild(e);
    }
    container.appendChild(entries);
}

void Charts_XmlExport::finalizeDocument()
{
    doc.appendChild(container);
}

Charts_XmlExport::TypeMap Charts_XmlExport::tmap = {
    {typeid(simple_bar_chart), 0},
    {typeid(stacked_bar_chart), 1},
    {typeid(pie_chart),2},
    {typeid(polar_chart), 3},
    {typeid(time_chart),4},
    {typeid(dot_chart),5}
};


