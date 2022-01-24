#ifndef PRESENTER_CHART_VIEW_H
#define PRESENTER_CHART_VIEW_H

#include <QObject>
#include <charts_main_window.h>
#include <charts_chartcreation.h>
#include <charts_comparisonchart_editor.h>
#include <model.h>

class presenter_chart_view : public QObject
{
    Q_OBJECT
private:
    Charts_Main_Window* charts_mw;
    Charts_ChartCreation* charts_creation;
    Charts_Comparisonchart_Editor* comp_editor;
    model* mod;
public:
    explicit presenter_chart_view(QObject *parent = nullptr);
    void set_model(model*);
    void set_mainchart_view(Charts_Main_Window*);
    void set_chartcreation_view(Charts_ChartCreation*);
    void set_comparisoneditor_view(Charts_Comparisonchart_Editor*);
    double* get_entries_value(uint);
    std::string get_label(uint);
public slots:
    void add_charts();
    void add_entry_comparison();
    void show_title();
};

#endif // PRESENTER_CHART_VIEW_H
