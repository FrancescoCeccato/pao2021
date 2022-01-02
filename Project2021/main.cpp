#include "charts_main_window.h"

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

    //Dialog_Entrance w;
    Charts_Main_Window w;
    w.show();
    return a.exec();

}
