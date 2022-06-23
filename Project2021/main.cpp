#include <presenter_chart_view.h>
#include <dialog_entrance.h>
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
    model* m = new model();
    presenter_chart_view* c = new presenter_chart_view();
    Dialog_Entrance* d = new Dialog_Entrance();
    c->set_model(m);
    c->set_dialogentrance_view(d);
    d->set_chart_presenter(c);

    d->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    d->show();


    return a.exec();
}
