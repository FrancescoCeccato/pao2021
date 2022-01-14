#include "charts_main_window.h"
#include "presenter_chart_view.h"
#include "model.h"
#include "charts_comparisonchart_editor.h"
#include "charts_cartesianchart_addpoints.h"
#include "charts_chartcreation.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <string>

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

    presenter_chart_view c;
    model m;
    Charts_Main_Window w;
    c.set_chart_view(&w);
    c.set_model(&m);
    w.set_chart_presenter(&c);
    //Dialog_Entrance w;

    w.show();
    //Charts_Cartesianchart_AddPoints* w = new Charts_Cartesianchart_AddPoints();
    //Charts_Comparisonchart_Editor* w = new Charts_Comparisonchart_Editor();
    //Charts_ChartCreation* w = new Charts_ChartCreation();
    //Charts_Main_Window* w = new Charts_Main_Window();

    //w->show();
    return a.exec();

}
