#ifndef PRESENTER_CHART_VIEW_H
#define PRESENTER_CHART_VIEW_H

#include <QObject>
#include <charts_main_window.h>
#include <model.h>

class presenter_chart_view : public QObject
{
    Q_OBJECT
private:
    Charts_Main_Window* charts_mw;
    model* mod;
public:
    explicit presenter_chart_view(QObject *parent = nullptr);
    void set_model(model*);
    void set_chart_view(Charts_Main_Window*);
public slots:
    void add_comparison_charts();
    void add_entry_comparison();
    void show_title();
};

#endif // PRESENTER_CHART_VIEW_H
