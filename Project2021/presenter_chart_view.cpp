#include <presenter_chart_view.h>
#include <comparison_chart.h>
#include <charts_exception.h>
#include <set>
#include <vector>

presenter_chart_view::presenter_chart_view(QObject *parent): QObject{parent} {}

void presenter_chart_view::set_model(model* m){ mod = m;}
void presenter_chart_view::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}
void presenter_chart_view::set_chartcreation_view(Charts_ChartCreation * ccc){ charts_creation = ccc;}
void presenter_chart_view::set_comparisoneditor_view(Charts_Comparisonchart_Editor *cce){ comp_editor = cce;}
void presenter_chart_view::set_cartesianeditor_view(Charts_Cartesianchart_AddPoints* cap){ cart_editor = cap;}
void presenter_chart_view::set_dialogentrance_view(Dialog_Entrance * d){de = d;}

void presenter_chart_view::create_views(){
    Charts_Main_Window* mw = new Charts_Main_Window();
    set_mainchart_view(mw);
    charts_mw->set_chart_presenter(this);
    charts_mw->showMaximized();
    Charts_Cartesianchart_AddPoints* cca = new Charts_Cartesianchart_AddPoints();
    set_cartesianeditor_view(cca);
    cart_editor->set_chart_presenter(this);
    Charts_Comparisonchart_Editor* cce = new Charts_Comparisonchart_Editor();
    cce->setWindowModality(Qt::ApplicationModal);
    set_comparisoneditor_view(cce);
    comp_editor->set_chart_presenter(this);
    charts_mw->show_charts(mod->get_chart());
    charts_mw->show_chart_info(mod->chart_info());
    charts_mw->showParent_list_values(mod->get_chart());
    if(type != 5){
        charts_mw->TC_SpinBox1->setEnabled(false);
        charts_mw->TC_SpinBox2->setEnabled(false);
        charts_mw->TC_Calculate->setEnabled(false);
    }
}

void presenter_chart_view::add_charts(){
    try{
        bool h = charts_creation->checkBox1->isChecked(), seg = charts_creation->checkBox2->isChecked();
        std::string title = charts_creation->chartTitle->text().toStdString(),
                x = charts_creation->axisX->text().toStdString(),
                y = charts_creation->axisY->text().toStdString();
        type = charts_creation->selected;
        uint amt = 1;
        if (type>=1 && type<=6 && title != "")
        {
            mod->add_charts(type, title, amt, h, seg, x, y);
            create_views();
            charts_creation->close();
            delete charts_creation;
        }else
            throw chart_not_valid();
    }
    catch(std::exception& ex){
        charts_creation->labelDescription->setText(ex.what());
    }
}

void presenter_chart_view::add_entry_comparison(){
    comp_editor->signalLabel->setText("");
    mod->set_amt(comp_editor->spinBox->value());
    bool stop = false;
    if(type == 2){
        std::pair<std::vector<std::string>,bool> cat = get_categories();
        if(cat.second)
            stop = true;
        else
            mod->set_categories(cat.first);
    }
    std::set<std::string> s;
    for(uint i = 0; i<20 && !stop;++i){
        stop = true;
        for(int j = 0; j<comp_editor->spinBox->value() && stop; ++j){
            QLineEdit* e = static_cast<QLineEdit*>(comp_editor->gridValues->cellWidget(j,i));
            if(e->text() != "")
                stop = false;
        }
        if(!stop){
            if(!s.insert(get_label(i)).second){
                comp_editor->signalLabel->setText("Due o più etichette coincidono!");
                stop = true;
            }
            else{
                comp_editor->signalLabel->setText("");
                mod->add_entry_comparison(get_entries_value(i), get_label(i),i);
            }
        }else
            mod->delete_entry_comparison(i);
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

std::pair<std::vector<std::string>,bool> presenter_chart_view::get_categories(){
    std::vector<std::string> categories;
    std::set<std::string> set_categories;
    bool stop = false;
    for(int i = 0; i<comp_editor->spinBox->value() && !stop;++i){
        if(comp_editor->gridLabelCategories->item(i, 0)){
            if(comp_editor->gridLabelCategories->item(i, 0)->text().toStdString() == ""){
                comp_editor->signalLabel->setText("Una o più categorie non sono state impostate!");
                stop = true;
            }
            else if(!set_categories.insert(comp_editor->gridLabelCategories->item(i, 0)->text().toStdString()).second){
                comp_editor->signalLabel->setText("Due o più categorie coincidono!");
                stop = true;
            }
            else
                categories.push_back(comp_editor->gridLabelCategories->item(i, 0)->text().toStdString());
        }else{
            comp_editor->signalLabel->setText("Una o più categorie non sono state impostate!");
            stop = true;
        }
    }
    return std::pair<std::vector<std::string>,bool>(categories,stop);
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
    uint code = charts_creation->selected;
    charts_creation->labelDescription->setText(QString::fromStdString(model::chart_description(code)));
}

void presenter_chart_view::save(){
    QFileDialog sfd(charts_mw, tr("Salva grafico"),
                    QDir::currentPath(),
                    tr("XML files (*.xml)"));
    sfd.setWindowModality(Qt::WindowModal);
    sfd.setAcceptMode(QFileDialog::AcceptSave);
    sfd.setDefaultSuffix(".xml");
    QString filename;
    if(sfd.exec() == QDialog::Accepted)
        filename = sfd.selectedFiles().first();
    if(filename == ""){
        charts_mw->statusBar()->showMessage("Salvataggio annullato.");
    }else{
        Charts_XmlExport c_export(mod->get_chart(),filename);
        c_export.exportContent();
        charts_mw->statusBar()->showMessage(filename);
    }

}

void presenter_chart_view::load(){
    QWidget* w;
    try{        
        if(de->isActiveWindow())
            w = de;
        else
            w = charts_mw;
        QFileDialog sfd(w, tr("Carica grafico"),
                        QDir::currentPath(),
                        tr("XML files (*.xml)"));
        sfd.setWindowModality(Qt::WindowModal);
        sfd.setAcceptMode(QFileDialog::AcceptOpen);
        QString filename;
        if(sfd.exec() == QDialog::Accepted)
            filename = sfd.selectedFiles().first();
        else
            throw no_chart_selected();
        Charts_XmlImport c_import(filename);
        std::pair<uint,chart*> ch = c_import.importContent();
        mod->set_chart(ch.second);
        type = ch.first+1;
        if(w == de){
            create_views();
            de->close();
        }
        charts_mw->show_charts(mod->get_chart());
        charts_mw->show_chart_info(mod->chart_info());
        charts_mw->showParent_list_values(mod->get_chart());
        if(type != 5){
            charts_mw->TC_SpinBox1->setEnabled(false);
            charts_mw->TC_SpinBox2->setEnabled(false);
            charts_mw->TC_Calculate->setEnabled(false);
        }
        charts_mw->statusBar()->showMessage(filename);
    }catch(std::ios_base::failure& ex){
        QMessageBox::about(w,"Errore",ex.what());
    }catch(std::logic_error& ex){
        QMessageBox::about(w,"Errore",ex.what());
    }catch(std::exception& ex){
        QMessageBox::about(w,"Errore",ex.what());
    }
}

void presenter_chart_view::open_new(){
    bool open = true;
    if(!de->isActiveWindow()){
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("Crea nuovo grafico");
        msgBox.setInformativeText("Vuoi salvare il grafico corrente?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Save:
              save();
              delete comp_editor;
              delete cart_editor;
              delete charts_mw;
              break;
          case QMessageBox::Close:
              delete comp_editor;
              delete cart_editor;
              delete charts_mw;
              break;
          case QMessageBox::Cancel:
              open = false;
              break;
          default:
              break;
        }
    }else{
        de->close();
    }
    if(open){
        Charts_ChartCreation* c = new Charts_ChartCreation();
        set_chartcreation_view(c);
        charts_creation->showMaximized();
        charts_creation->set_chart_presenter(this);
    }
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



