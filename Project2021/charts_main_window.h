#ifndef CHARTS_MAIN_WINDOW_H
#define CHARTS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QHBoxLayout>
#include <chart.h>
#include <charts_comparisonchart_editor.h>

class presenter_chart_view;


class Charts_Main_Window : public QMainWindow
{
    Q_OBJECT

private:
    presenter_chart_view* c;
    Charts_Comparisonchart_Editor* comp_editor;
public:
    QChartView *chartView;
    QTreeWidget *valuesList;
    QListWidget *statsList;
    QPushButton *zoomIn, *zoomOut, *repaint, *settings, *TC_Calculate;
    QLabel *TC_Result;
    QSpinBox *TC_SpinBox1, *TC_SpinBox2;
    QToolBar *toolBarBottom;
    //test
public:
    explicit Charts_Main_Window(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
    void set_comparison_editor(Charts_Comparisonchart_Editor* cce);
    void set_text(std::string);
    void show_charts(chart*);
    void show_simple_bar_chart(chart*);
    void show_stacked_bar_chart(chart*);
    void show_pie_chart(chart*);
    void show_time_chart(chart*);
    void showParent_list_values(chart*);
    void showChild_list_values(QTreeWidgetItem* ,const chart*, uint);
    void delete_list_values(chart*);

signals:

public slots:
    void open_settings();

};

#endif // CHARTS_MAIN_WINDOW_H
