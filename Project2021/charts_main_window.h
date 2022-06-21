#ifndef CHARTS_MAIN_WINDOW_H
#define CHARTS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QHBoxLayout>
#include <chart.h>

class presenter_chart_view;


class Charts_Main_Window : public QMainWindow
{
    Q_OBJECT

private:
    presenter_chart_view* c;
public:
    QChartView *chartView;
    QTreeWidget *valuesList;
    QListWidget *statsList;
    QPushButton *zoomIn, *zoomOut, *repaint, *settings, *TC_Calculate;
    QLabel *TC_Result;
    QSpinBox *TC_SpinBox1, *TC_SpinBox2;
    QToolBar *toolBarBottom, *toolBarTop;
    QMenu *deleteP;
public:
    explicit Charts_Main_Window(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view*);

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
    void show_chart_info(std::vector<std::string>);
    void closeEvent(QCloseEvent *);
public slots:
    void menu_delete( const QPoint & pos );
    void expand_pie_chart();
};

#endif // CHARTS_MAIN_WINDOW_H
