#include "main_window.h"
#include <QLayout>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <controller_chart_view.h>

#define BTN_SIDE 200

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow{parent}
{
    this->statusBar()->showMessage("porcodio");
    auto menu = new QMenu();
    menu->addMenu("porcodio");
    menu->addMenu("oof");
    menu->setTitle("uno");
    this->menuBar()->addMenu(menu);
    this->menuBar()->addMenu("Due");

    QPalette pal1 = QPalette();
    pal1.setColor(QPalette::Window, QColor(135,235,255));
    QPalette pal2 = QPalette();
    pal2.setColor(QPalette::Window, QColor::fromRgb(255,255,255));

    mainLayout = new QHBoxLayout();
    elementsLeft = new QVBoxLayout();
    elementsCenter = new QVBoxLayout();
    elementsRight = new QVBoxLayout();

    QChart* chart = new QChart();
    chart->setTitle("Test");
    QBarSet* set1 = new QBarSet("Voti");
    *set1 << 6 << 7 << 6 << 8 << 7;
    QBarSeries* series1 = new QBarSeries();
    series1->append(set1);
    chart->addSeries(series1);
    QStringList label;
    label << "voto 1" << "voto 2" << "voto 3" << "voto 4" << "voto 5";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(label);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 10);
    //chart->createDefaultAxes();
    //chart->setAxisX(axis, series1);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignLeft);
    chartView = new QChartView(chart);
    elementsCenter->addWidget(chartView);
    elementsLeft->addWidget(new QPushButton("oof"));

    this->setCentralWidget(chartView);

    QDockWidget* dock1 = new QDockWidget(this);
    dock1->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    zoomIn = new QPushButton();
    zoomIn->setFixedSize(BTN_SIDE,BTN_SIDE);

    QDockWidget* dock2 = new QDockWidget(this);
    dock2->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    zoomOut = new QPushButton();
    zoomOut->setFixedSize(BTN_SIDE,BTN_SIDE);

    QDockWidget* dock3 = new QDockWidget(this);
    dock3->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock3->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    repaint = new QPushButton();
    repaint->setFixedSize(BTN_SIDE,BTN_SIDE);

    QDockWidget* dock4 = new QDockWidget("LISTA DEI VALORI",this);
    dock4->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock4->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto valuesList = new QListView();

    QDockWidget* dock5 = new QDockWidget("MODIFICA COLLEZIONE...",this);
    dock5->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock5->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    auto btnModifyCollection = new QPushButton();

    dock1->setWidget(zoomIn);
    dock2->setWidget(zoomOut);
    dock3->setWidget(repaint);
    dock4->setWidget(valuesList);
    dock5->setWidget(btnModifyCollection);

    addDockWidget(Qt::LeftDockWidgetArea, dock1);
    addDockWidget(Qt::LeftDockWidgetArea, dock2);
    addDockWidget(Qt::LeftDockWidgetArea, dock3);
    addDockWidget(Qt::RightDockWidgetArea, dock4);
    addDockWidget(Qt::RightDockWidgetArea, dock5);

    this->setPalette(pal1);
    this->statusBar()->setPalette(pal2);
    this->menuBar()->setPalette(pal2);
}
