#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QHBoxLayout>

class Main_Window : public QMainWindow
{
    Q_OBJECT
private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *elementsLeft, *elementsRight, *elementsCenter;
    QChartView *chartView;

    QPushButton *zoomIn, *zoomOut, *repaint;


public:
    explicit Main_Window(QWidget *parent = nullptr);

signals:

};

#endif // MAIN_WINDOW_H
