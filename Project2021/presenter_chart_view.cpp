#include "presenter_chart_view.h"
#include "comparison_chart.h"
#include "iostream"

presenter_chart_view::presenter_chart_view(QObject *parent): QObject{parent} {}

void presenter_chart_view::set_model(model* m){ mod = m;}

void presenter_chart_view::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}
void presenter_chart_view::set_chartcreation_view(Charts_ChartCreation * ccc){ charts_creation = ccc;}
void presenter_chart_view::set_comparisoneditor_view(Charts_Comparisonchart_Editor *cce){ comp_editor = cce;}
void presenter_chart_view::set_cartesianeditor_view(Charts_Cartesianchart_AddPoints* cap){ cart_editor = cap;}

void presenter_chart_view::add_charts(){
    bool h = charts_creation->checkBox1->isChecked(), seg = charts_creation->checkBox2->isChecked();
    std::string title = charts_creation->chartTitle->text().toStdString(), x, y;
    uint code = get_selected(), amt = 1;
    mod->add_charts(code, title, amt, h, seg, x, y);
    charts_mw->show();
    charts_creation->close();
    charts_mw->show_charts(mod->get_chart());
    charts_mw->show_chart_info(mod->chart_info());
}

void presenter_chart_view::add_entry_comparison(){
    bool stop = false;
    for(uint i = 0; i<20 && !stop;++i){
        stop = true;
        for(int j = 0; j<comp_editor->spinBox->value() && stop; ++j){
            if(comp_editor->gridValues->item(j,i) && comp_editor->gridValues->item(j,i)->text() != "")
                stop = false;
        }
        if(!stop){
            mod->add_entry_comparison(get_entries_value(i), get_label(i),i);
        }else if(stop){
            mod->delete_entry_comparison(i);
        }
    }
    charts_mw->show_charts(mod->get_chart());
    charts_mw->showParent_list_values(mod->get_chart());
    charts_mw->show_chart_info(mod->chart_info());
}

void presenter_chart_view::add_point(){
    float x = cart_editor->spinX->value();
    float y = cart_editor->spinY->value();
    mod->add_point(x,y);
    charts_mw->show_charts(mod->get_chart());
    charts_mw->showParent_list_values(mod->get_chart());
}

void presenter_chart_view::delete_point(){
    QTreeWidgetItem *nd = charts_mw->valuesList->currentItem();
    uint index = charts_mw->valuesList->indexOfTopLevelItem(nd);
    mod->delete_point(index);
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

uint presenter_chart_view::get_selected(){
    return charts_creation->selected;
}

void presenter_chart_view::open_settings(){
    comparison_chart* cc = static_cast<comparison_chart*>(mod->get_chart());
    if(get_selected() == 1 || get_selected() == 2 || get_selected() == 3|| get_selected() == 4){
        comp_editor->show();
        if(get_selected() != 2){
            comp_editor->spinBox->setValue(1);
            comp_editor->spinBox->setEnabled(false);
            comp_editor->gridValues->clear();
            comp_editor->gridCategories->clear();
            comp_editor->gridValues->setRowCount(1);
            comp_editor->set_grids(cc);
        }
    }else{
        cart_editor->show();
    }
}

void presenter_chart_view::give_balance(){
    float x1 = charts_mw->TC_SpinBox1->value(), x2 = charts_mw->TC_SpinBox2->value();
    charts_mw->TC_Result->setText(QString::number(mod->give_balance(x1,x2)));
}

