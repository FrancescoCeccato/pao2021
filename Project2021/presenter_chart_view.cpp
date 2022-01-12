#include "presenter_chart_view.h"

presenter_chart_view::presenter_chart_view(QObject *parent): QObject{parent} {}

void presenter_chart_view::set_model(model* m){ mod = m;}

void presenter_chart_view::set_chart_view(Charts_Main_Window* cmw){charts_mw = cmw;}

void presenter_chart_view::add_comparison_charts(){
    bool h = false, seg = false;
    std::string title = charts_mw->prova->text().toStdString();
    uint code = 1, amt = 1;
    mod->add_comparison_charts(code, title, amt, h, seg);
    show_title();
}

void presenter_chart_view::add_entry_comparison(){
    try{
        uint code = 1;
        double* d = new double[1] {7};
        std::string label = "Voto";
        mod->add_entry_comparison(code, d, label);
    }
    catch(std::runtime_error exc){

    }
    charts_mw->show_simple_bar_chart(mod->get_chart());
}

void presenter_chart_view::show_title(){
    //charts_mw->set_text(mod->get_title());
    //charts_mw->set_text("Prova");
    std::string t = mod->get_title();
    charts_mw->set_text(t);
}
