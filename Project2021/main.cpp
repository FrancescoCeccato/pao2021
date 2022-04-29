/*
#include "charts_main_window.h"
#include "presenter_chart_view.h"
#include "model.h"
#include "charts_comparisonchart_editor.h"
#include "charts_cartesianchart_addpoints.h"
#include "charts_chartcreation.h"
*/
#include "chart.h"
#include "charts_xmlexport.h"
#include "charts_xmlimport.h"
#include "stacked_bar_chart.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Project2021_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    /*
    presenter_chart_view* c = new presenter_chart_view();
    model* m = new model();
    Charts_Main_Window* mw = new Charts_Main_Window();
    Charts_ChartCreation* w = new Charts_ChartCreation();

    Charts_Comparisonchart_Editor* e = new Charts_Comparisonchart_Editor();
    Charts_Cartesianchart_AddPoints* ap = new Charts_Cartesianchart_AddPoints();
    c->set_chartcreation_view(w);
    c->set_mainchart_view(mw);
    c->set_comparisoneditor_view(e);
    c->set_cartesianeditor_view(ap);
    c->set_model(m);
    mw->set_comparison_editor(e);
    mw->set_cartesian_editor(ap);
    mw->set_chart_presenter(c);
    w->set_chart_presenter(c);
    e->set_mainchart_view(mw);
    e->set_chart_presenter(c);
    ap->set_mainchart_view(mw);
    ap->set_chart_presenter(c);

    w->show();
    return a.exec();
}
