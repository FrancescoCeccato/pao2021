#include "dialog_entrance.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "pie_chart.h"
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
    pie_chart p = pie_chart("prova");
    p.add_entry(18, "audi");
    p.add_entry(24, "mercedes");
    p.add_entry(52, "fiat");
    p.add_entry(11, "chevrolet");
    p.add_entry(63, "volkswagen");
    std::cout<<p.give_slice_percentage(2)<<std::endl;
    std::cout<<p.give_max().second<<std::endl;
    /*
    Dialog_Entrance w;
    w.show();
    return a.exec();
    */
}
