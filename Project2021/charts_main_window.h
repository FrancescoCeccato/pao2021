#ifndef CHARTS_MAIN_WINDOW_H
#define CHARTS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QHBoxLayout>
#include <chart.h>
#include <charts_comparisonchart_editor.h>
#include <charts_cartesianchart_addpoints.h>

class presenter_chart_view;


class Charts_Main_Window : public QMainWindow
{
    Q_OBJECT

private:
    presenter_chart_view* c;
    Charts_Comparisonchart_Editor* comp_editor;
    Charts_Cartesianchart_AddPoints* cart_editor;
    QMenu *deleteP;
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
    void set_chart_presenter(presenter_chart_view*);
    void set_comparison_editor(Charts_Comparisonchart_Editor*);
    void set_cartesian_editor(Charts_Cartesianchart_AddPoints*);
    void show_charts(chart*);
    void show_simple_bar_chart(chart*);
    void show_stacked_bar_chart(chart*);
    void show_segmented_bar_chart(chart*);
    void show_pie_chart(chart*);
    void show_polar_chart(chart*);
    void show_time_chart(chart*);
    void show_dot_chart(chart*);
    void showParent_list_values(chart*);
    void showChild_list_values(QTreeWidgetItem* ,const chart*, uint);
    void delete_list_values(chart*);
    void show_chart_info(std::vector<std::string>);
signals:

public slots:
    void menu_delete( const QPoint & pos );
    void expand_pie_chart();

};

#endif // CHARTS_MAIN_WINDOW_H
