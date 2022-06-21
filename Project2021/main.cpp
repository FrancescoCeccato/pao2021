//#include <charts_main_window.h>
#include <presenter_chart_view.h>
//#include <model.h>
//#include "charts_comparisonchart_editor.h"
//#include "charts_cartesianchart_addpoints.h"
//#include "charts_chartcreation.h"
#include <dialog_entrance.h>
//#include "chart.h"
//#include "charts_xmlexport.h"
//#include "charts_xmlimport.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

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
    presenter_chart_view* c = new presenter_chart_view();
    Dialog_Entrance* d = new Dialog_Entrance();

    c->set_dialogentrance_view(d);
    d->set_chart_presenter(c);


    d->show();
    return a.exec();
}
