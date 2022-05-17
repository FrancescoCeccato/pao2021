#include <presenter_chart_view.h>
#include <comparison_chart.h>
#include <charts_exception.h>


presenter_chart_view::presenter_chart_view(QObject *parent): QObject{parent} {}

void presenter_chart_view::set_model(model* m){ mod = m;}
void presenter_chart_view::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}
void presenter_chart_view::set_chartcreation_view(Charts_ChartCreation * ccc){ charts_creation = ccc;}
void presenter_chart_view::set_comparisoneditor_view(Charts_Comparisonchart_Editor *cce){ comp_editor = cce;}
void presenter_chart_view::set_cartesianeditor_view(Charts_Cartesianchart_AddPoints* cap){ cart_editor = cap;}
void presenter_chart_view::set_dialogentrance_view(Dialog_Entrance * d){de = d;}

void presenter_chart_view::add_charts(){
    try{
        bool h = charts_creation->checkBox1->isChecked(), seg = charts_creation->checkBox2->isChecked();
        std::string title = charts_creation->chartTitle->text().toStdString(),
                x = charts_creation->axisX->text().toStdString(),
                y = charts_creation->axisY->text().toStdString();
        type = charts_creation->selected;
        uint amt = 1;
        if (type>=1 && type<=6)
        {
            model* m = new model();
            set_model(m);
            mod->add_charts(type, title, amt, h, seg, x, y);
            Charts_Main_Window* mw = new Charts_Main_Window();
            set_mainchart_view(mw);
            charts_mw->set_chart_presenter(this);
            charts_mw->showMaximized();
            charts_mw->show_charts(mod->get_chart());
            charts_mw->show_chart_info(mod->chart_info());
            charts_creation->close();
            delete charts_creation;
            if(type != 5){
                charts_mw->TC_SpinBox1->setEnabled(false);
                charts_mw->TC_SpinBox2->setEnabled(false);
                charts_mw->TC_Calculate->setEnabled(false);
            }
            Charts_Cartesianchart_AddPoints* cca = new Charts_Cartesianchart_AddPoints();
            set_cartesianeditor_view(cca);
            cart_editor->set_mainchart_view(charts_mw);
            cart_editor->set_chart_presenter(this);
            Charts_Comparisonchart_Editor* cce = new Charts_Comparisonchart_Editor();
            set_comparisoneditor_view(cce);
            comp_editor->set_mainchart_view(charts_mw);
            comp_editor->set_chart_presenter(this);
        }else
            throw chart_not_valid();
    }catch(std::exception& ex){
        charts_creation->labelDescription->setText(ex.what());
    }
}

void presenter_chart_view::add_entry_comparison(){
    mod->set_amt(comp_editor->spinBox->value());
    bool stop = false;
    if(type == 2)
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
        charts_mw->show_chart_info(mod->chart_info());
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
    charts_mw->show_chart_info(mod->chart_info());
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

void presenter_chart_view::open_settings(){
    comparison_chart* cc = static_cast<comparison_chart*>(mod->get_chart());
    if(type >= 1 && type <= 4){
        comp_editor->show();
        if(type != 2){
            comp_editor->spinBox->setValue(1);
            comp_editor->spinBox->setEnabled(false);
            comp_editor->gridValues->setRowCount(1);
            comp_editor->set_grids(cc);
            comp_editor->gridLabelCategories->setVisible(false);
            comp_editor->label3->setVisible(false);
        }else{
             comp_editor->spinBox->setValue(cc->get_nvalues());
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
        QDoubleValidator* val;
        if(type!=4){
            val = new QDoubleValidator(0.0,1000.00,2);
            val->setNotation(QDoubleValidator::StandardNotation);
            val->setLocale(QLocale("us_US"));
        }
        else{
            val = new QDoubleValidator(0.0,10.0,1);
            val->setNotation(QDoubleValidator::StandardNotation);
            val->setLocale(QLocale("us_US"));
        }
        line->setValidator(val);
        comp_editor->gridValues->setCellWidget(row,col,line);
     }
}

void presenter_chart_view::populateRow(){
    int new_nrow = comp_editor->spinBox->value();
    int nrow = comp_editor->gridValues->rowCount();
    comp_editor->gridLabelCategories->setRowCount(new_nrow);
    comp_editor->gridValues->setRowCount(new_nrow);
    if(new_nrow>nrow){
        populateRowWithLineEdit(new_nrow-1);
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
    uint code = type;
    charts_creation->labelDescription->setText(QString::fromStdString(model::chart_description(code)));
}

void presenter_chart_view::save(){
    QString directory = QFileDialog::getSaveFileName(charts_mw, tr("Salva grafico"),
                               QDir::currentPath(),
                               tr("XML files (*.xml)"));
    QString nome_file = QFileInfo(directory).fileName();
    if(nome_file == ""){
        charts_mw->statusBar()->showMessage("Salvataggio annullato.");
    }else{
        Charts_XmlExport c_export(mod->get_chart(),directory,nome_file);
        c_export.exportContent();
        charts_mw->statusBar()->showMessage(directory);
    }

}

void presenter_chart_view::load(){
    QWidget* w;
    try{        
        if(de->isActiveWindow())
            w = de;
        else
            w = charts_mw;
        QString directory = QFileDialog::getOpenFileName(w, tr("Carica grafico"),
                                                         QDir::currentPath(),
                                                         tr("XML files (*.xml)"));
        QString nome_file = QFileInfo(directory).fileName();
        Charts_XmlImport c_import(directory,nome_file);
        std::pair<uint,chart*> ch = c_import.importContent();
        if(de->isActiveWindow()){
            Charts_Main_Window* mw = new Charts_Main_Window();
            set_mainchart_view(mw);
            charts_mw->showMaximized();
            charts_mw->set_chart_presenter(this);
            Charts_Cartesianchart_AddPoints* cca = new Charts_Cartesianchart_AddPoints();
            set_cartesianeditor_view(cca);
            cart_editor->set_mainchart_view(charts_mw);
            cart_editor->set_chart_presenter(this);
            Charts_Comparisonchart_Editor* cce = new Charts_Comparisonchart_Editor();
            set_comparisoneditor_view(cce);
            comp_editor->set_mainchart_view(charts_mw);
            comp_editor->set_chart_presenter(this);
            de->close();
        }
        model* m = new model();
        set_model(m);
        mod->set_chart(ch.second);
        type = ch.first+1;
        charts_mw->show_charts(mod->get_chart());
        charts_mw->show_chart_info(mod->chart_info());
        charts_mw->showParent_list_values(mod->get_chart());
        if(ch.first != 5){
            charts_mw->TC_SpinBox1->setEnabled(false);
            charts_mw->TC_SpinBox2->setEnabled(false);
            charts_mw->TC_Calculate->setEnabled(false);
        }
        charts_mw->statusBar()->showMessage(directory);
    }catch(std::ios_base::failure& ex){
        QMessageBox::about(w,"Errore",ex.what());
    }catch(std::logic_error& ex){
        QMessageBox::about(w,"Errore",ex.what());
    }
}

void presenter_chart_view::open_new(){
    if(!de->isActiveWindow()){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setWindowTitle("Crea nuovo grafico");
        msgBox.setText("Vuoi salvare il grafico corrente?");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes){
          save();
        }
        delete comp_editor;
        delete cart_editor;
        delete charts_mw;
    }else{
        de->close();
    }
    Charts_ChartCreation* c = new Charts_ChartCreation();
    set_chartcreation_view(c);
    charts_creation->showMaximized();
    charts_creation->set_chart_presenter(this);
}

void presenter_chart_view::close(bool salva){
    if(salva){
        save();
    }
    delete de;
    comp_editor->close();
    delete comp_editor;
    cart_editor->close();
    delete cart_editor;
    delete charts_mw;
    delete mod;
}

uint presenter_chart_view::type = 0;



