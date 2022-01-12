#ifndef CHARTS_MAIN_WINDOW_H
#define CHARTS_MAIN_WINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QHBoxLayout>

class Charts_Main_Window : public QMainWindow
{
    Q_OBJECT
public:
    QChartView *chartView;
    QTreeWidget *valuesList;
    QListWidget *statsList;
    QPushButton *zoomIn, *zoomOut, *repaint, *settings, *TC_Calculate;
    QLabel *TC_Result;
    QSpinBox *TC_SpinBox1, *TC_SpinBox2;
    QToolBar *toolBarBottom;
    explicit Charts_Main_Window(QWidget *parent = nullptr);

signals:

};

#endif // CHARTS_MAIN_WINDOW_H
