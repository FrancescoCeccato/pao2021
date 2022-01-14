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
    QToolBar *toolBarBottom;
    //test
public:
    QLineEdit *prova;
    QPushButton *crea;

public:
    explicit Charts_Main_Window(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
    void set_text(std::string);
    void show_simple_bar_chart(const chart*);
    void show_stacked_bar_chart(const chart*);
    void show_pie_chart(const chart*);
    void show_time_chart(const chart*);

signals:

};

#endif // CHARTS_MAIN_WINDOW_H
