#include "presenter_chart_view.h"
#include "comparison_chart.h"
#include "iostream"

presenter_chart_view::presenter_chart_view(QObject *parent): QObject{parent} {}

void presenter_chart_view::set_model(model* m){ mod = m;}

void presenter_chart_view::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}
void presenter_chart_view::set_chartcreation_view(Charts_ChartCreation * ccc){ charts_creation = ccc;}
void presenter_chart_view::set_comparisoneditor_view(Charts_Comparisonchart_Editor *cce){ comp_editor = cce;}

void presenter_chart_view::add_charts(){
    bool h = charts_creation->checkBox1->isChecked(), seg = charts_creation->checkBox2->isChecked();
    std::string title = charts_creation->chartTitle->text().toStdString(), x, y;
    uint code = charts_creation->selected, amt = 1;
    mod->add_charts(code, title, amt, h, seg, x, y);
    charts_mw->show();
    charts_creation->close();
    charts_mw->set_chart_presenter(this);
    charts_mw->show_charts(mod->get_chart());
    show_title();
}

void presenter_chart_view::add_entry_comparison(){
    uint code = charts_creation->selected;
    bool stop = false;
    for(uint i = 0; i<20 && !stop;++i){
        stop = true;
        for(int j = 0; j<comp_editor->spinBox->value() && stop; ++j){
            if(comp_editor->gridValues->item(j,i))
                stop = false;
        }
        if(!stop){
            mod->delete_entries(i);
            mod->add_entry_comparison(code, get_entries_value(i), get_label(i));
        }
    }
    charts_mw->show_charts(mod->get_chart());
    charts_mw->showParent_list_values(mod->get_chart());
}

double* presenter_chart_view::get_entries_value(uint index){
    int length = comp_editor->spinBox->value();
    double* value = new double();
    for(int j = 0; j<length; ++j){
        if(comp_editor->gridValues->item(j,index)){
            value[j] = comp_editor->gridValues->item(j,index)->text().toDouble();
        } else
            value[j] = 0;
    }
    return value;
}

std::string presenter_chart_view::get_label(uint index){
    std::string label = "";
    if(comp_editor->gridCategories->item(index,0)){
        label = comp_editor->gridCategories->item(index,0)->text().toStdString();
    } else
        label = "";
    return label;
}

void presenter_chart_view::show_title(){
    std::string t = mod->get_title();
    charts_mw->set_text(t);
}
