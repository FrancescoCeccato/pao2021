#include "presenter_chart_view.h"
#include "comparison_chart.h"
#include "charts_exception.h"
#include "iostream"


presenter_chart_view::presenter_chart_view(QObject *parent): QObject{parent} {}

void presenter_chart_view::set_model(model* m){ mod = m;}
void presenter_chart_view::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}
void presenter_chart_view::set_chartcreation_view(Charts_ChartCreation * ccc){ charts_creation = ccc;}
void presenter_chart_view::set_comparisoneditor_view(Charts_Comparisonchart_Editor *cce){ comp_editor = cce;}
void presenter_chart_view::set_cartesianeditor_view(Charts_Cartesianchart_AddPoints* cap){ cart_editor = cap;}

void presenter_chart_view::add_charts(){
    try{
        bool h = charts_creation->checkBox1->isChecked(), seg = charts_creation->checkBox2->isChecked();
        std::string title = charts_creation->chartTitle->text().toStdString(),
                x = charts_creation->axisX->text().toStdString(),
                y = charts_creation->axisY->text().toStdString();
        uint code = get_selected(), amt = 1;
        if (code>=1 && code<=6)
        {
            mod->add_charts(code, title, amt, h, seg, x, y);
            charts_mw->showMaximized();
            charts_creation->close();
            charts_mw->show_charts(mod->get_chart());
            charts_mw->show_chart_info(mod->chart_info());
            if(code != 5){
                charts_mw->TC_SpinBox1->setEnabled(false);
                charts_mw->TC_SpinBox2->setEnabled(false);
                charts_mw->TC_Calculate->setEnabled(false);
            }
        }else
            throw chart_not_valid();
    }catch(std::exception& ex){
        charts_creation->labelDescription->setText(ex.what());
    }

}

void presenter_chart_view::add_entry_comparison(){
    bool stop = false;
    if(get_selected() == 2)
        mod->set_categories(get_categories());
    for(uint i = 0; i<20 && !stop;++i){
        stop = true;
        for(int j = 0; j<comp_editor->spinBox->value() && stop; ++j){
            QLineEdit* e = static_cast<QLineEdit*>(comp_editor->gridValues->cellWidget(j,i));
            if(e->text() != "")
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
    try{
        mod->add_point(x,y);
        charts_mw->show_charts(mod->get_chart());
        charts_mw->showParent_list_values(mod->get_chart());
        cart_editor->signalLabel->setText("");
    }catch(std::exception& ex){
        cart_editor->signalLabel->setText(ex.what());
    }
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
    double* value = new double[length]();
    for(int j = 0; j<length; ++j){
        value[j] = getCellNumericValue(j,index);
    }
    return value;
}

std::string presenter_chart_view::get_label(uint index){
    std::string label = "";
    if(comp_editor->gridLabelEntries->item(0,index)){
        label = comp_editor->gridLabelEntries->item(0,index)->text().toStdString();
    } else
        label = "";
    return label;
}

std::vector<std::string> presenter_chart_view::get_categories(){
    std::vector<std::string> categories;
    for(int i = 0; i<comp_editor->spinBox->value();++i){
        if(comp_editor->gridLabelCategories->item(i, 0)){
            categories.push_back(comp_editor->gridLabelCategories->item(i, 0)->text().toStdString());
        }else{
            categories.push_back("");
        }
    }
    return categories;
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
            comp_editor->gridValues->setRowCount(1);
            comp_editor->set_grids(cc);
            comp_editor->gridLabelCategories->setVisible(false);
            comp_editor->label3->setVisible(false);
        }else{
             comp_editor->gridLabelCategories->setRowCount(comp_editor->spinBox->value());
             comp_editor->gridValues->setRowCount(comp_editor->spinBox->value());
             comp_editor->set_grids(cc);
        }
    }else{
        cart_editor->show();
    }
}

void presenter_chart_view::populateRowWithLineEdit(uint row) {
    for(int col = 0; col<20; col++) {
        auto line = new QLineEdit();
        line->setValidator(new QDoubleValidator());
        comp_editor->gridValues->setCellWidget(row,col,line);
     }
}

double presenter_chart_view::getCellNumericValue(uint row, uint col) {
    return static_cast<QLineEdit*>(comp_editor->gridValues->cellWidget(row, col))->text().toDouble();
}

void presenter_chart_view::give_balance(){
    float x1 = charts_mw->TC_SpinBox1->value(), x2 = charts_mw->TC_SpinBox2->value();
    try{
        charts_mw->TC_Result->setStyleSheet("QLabel { color : black; }");
        charts_mw->TC_Result->setText(QString::number(mod->give_balance(x1,x2)));
    }catch(std::exception& ex){
        charts_mw->TC_Result->setStyleSheet("QLabel { color : red; }");
        charts_mw->TC_Result->setText(ex.what());
    }
}

void presenter_chart_view::set_description(){
    uint code = get_selected();
    charts_creation->labelDescription->setText(QString::fromStdString(model::chart_description(code)));
}

void presenter_chart_view::save(){
    x.write_xml(mod->get_chart());
}

void presenter_chart_view::populateRow(){
    int new_nrow = comp_editor->spinBox->value();
    int nrow = comp_editor->gridValues->rowCount();
    comp_editor->gridLabelCategories->setRowCount(new_nrow);
    comp_editor->gridValues->setRowCount(new_nrow);
    mod->set_amt(new_nrow);
    if(new_nrow>nrow){
        populateRowWithLineEdit(new_nrow-1);
    }

}



