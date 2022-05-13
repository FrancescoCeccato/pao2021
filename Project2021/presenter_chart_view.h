#ifndef PRESENTER_CHART_VIEW_H
#define PRESENTER_CHART_VIEW_H

#include <QObject>
#include <QFileDialog>
#include <charts_main_window.h>
#include <charts_chartcreation.h>
#include <charts_comparisonchart_editor.h>
#include <charts_cartesianchart_addpoints.h>
#include <model.h>
#include <charts_xmlexport.h>
#include <charts_xmlimport.h>
#include <dialog_entrance.h>

class presenter_chart_view : public QObject
{
    Q_OBJECT
private:
    Charts_Main_Window* charts_mw;
    Charts_ChartCreation* charts_creation;
    Charts_Comparisonchart_Editor* comp_editor;
    Charts_Cartesianchart_AddPoints* cart_editor;
    model* mod;
    Dialog_Entrance* de;
public:
    explicit presenter_chart_view(QObject *parent = nullptr);
    void set_model(model*);
    void set_mainchart_view(Charts_Main_Window*);
    void set_chartcreation_view(Charts_ChartCreation*);
    void set_comparisoneditor_view(Charts_Comparisonchart_Editor*);
    void set_cartesianeditor_view(Charts_Cartesianchart_AddPoints*);
    void set_dialogentrance_view(Dialog_Entrance*);
    void populateRowWithLineEdit(uint index);
    void close(bool);
    static uint type;
private:
    double getCellNumericValue(uint row, uint col);
    double* get_entries_value(uint);
    std::string get_label(uint);
    std::vector<std::string> get_categories();

public slots:
    void add_charts();
    void add_entry_comparison();
    void add_point();
    void delete_point();
    void open_settings();
    void populateRow();
    void give_balance();
    void set_description();
    void save();
    void load();
    void open_new();
};

#endif // PRESENTER_CHART_VIEW_H
