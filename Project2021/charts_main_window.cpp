#include "charts_main_window.h"
#include <QLayout>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>

#define BTN_SIDE 100

Charts_Main_Window::Charts_Main_Window(QWidget *parent)
    : QMainWindow{parent}
{
    this->statusBar()->showMessage("porcodio");
    this->menuBar()->addAction("Guida...");

    QPalette pal1 = QPalette();
    pal1.setColor(QPalette::Window, QColor(200,235,255));
    QPalette pal2 = QPalette();
    pal2.setColor(QPalette::Background, QColor(255,255,255));

    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    this->setCentralWidget(chartView);

    QDockWidget* dock1 = new QDockWidget("LISTA DEI VALORI",this);
    dock1->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock1->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    valuesList = new QTreeWidget();
    QList<QString> list;
    list.append("oof");
    list.append("mock statale");
    list.append("vafangul");
    QStringList strings(list);
    auto item1 = new QTreeWidgetItem();
    item1->setText(0,"oof");
    QPixmap p(":/images/square.png");
    QIcon iconDot(p);
    item1->setIcon(0,iconDot);
    auto item2 = new QTreeWidgetItem();
    item2->setText(0,"demented");
    auto item = new QTreeWidgetItem(list);
    item1->addChild(item2);
    valuesList->addTopLevelItem(item1);


    QDockWidget* dock2 = new QDockWidget("MODIFICA COLLEZIONE...",this);
    dock2->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    settings = new QPushButton();
    QPixmap pixmap1(":/images/pencil.png");
    QIcon ButtonIcon1(pixmap1);
    settings->setIconSize(QSize(0.75*BTN_SIDE,0.75*BTN_SIDE));
    settings->setIcon(ButtonIcon1);
    settings->setCursor(Qt::CursorShape::PointingHandCursor);

    QDockWidget* dock3 = new QDockWidget("STATISTICHE DI RIEPILOGO",this);
    dock3->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock3->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    statsList = new QListWidget();
    statsList->addItem("oof");
    statsList->addItem("ouch");
    statsList->setStyleSheet("QListWidget::item { border-bottom: 1px solid lightgray; padding: 2px; }");

    QDockWidget* dock4 = new QDockWidget("CALCOLO BILANCIO",this);
    dock4->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock4->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    auto grid = new QGridLayout();
    TC_SpinBox1 = new QSpinBox();
    TC_SpinBox2 = new QSpinBox();
    TC_Calculate = new QPushButton("CALCOLA");
    TC_Result = new QLabel("oofiest");
    TC_Result->setStyleSheet("QLabel { color : black; }");
    TC_Result->setAlignment(Qt::AlignCenter);
    TC_Result->setFrameShape(QFrame::Panel);
    TC_Result->setFrameShadow(QFrame::Sunken);

    auto label1 = new QLabel("INIZIO");
    auto label2 = new QLabel("FINE");
    grid->addWidget(label1,0,0);
    grid->addWidget(label2,0,1);
    grid->addWidget(TC_SpinBox1,1,0);
    grid->addWidget(TC_SpinBox2,1,1);
    grid->addWidget(TC_Calculate,2,0);
    grid->addWidget(TC_Result,2,1);
    grid->setRowStretch(0|1|2,1);
    grid->setColumnStretch(0|1,1);
    auto widgetMock = new QWidget();
    widgetMock->setLayout(grid);

    dock1->setWidget(valuesList);
    dock2->setWidget(settings);
    dock3->setWidget(statsList);
    dock4->setWidget(widgetMock);

    addDockWidget(Qt::LeftDockWidgetArea, dock1);
    addDockWidget(Qt::RightDockWidgetArea, dock2);
    addDockWidget(Qt::BottomDockWidgetArea, dock3);
    addDockWidget(Qt::RightDockWidgetArea, dock4);

    setCorner(Qt::BottomRightCorner,Qt::BottomDockWidgetArea);
    setCorner(Qt::TopRightCorner,Qt::RightDockWidgetArea);
    setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);
    setCorner(Qt::TopLeftCorner,Qt::LeftDockWidgetArea);

    QToolBar* toolBarTop = new QToolBar();
    QPixmap pixmap2(":/images/new.png");
    QIcon ButtonIcon2(pixmap2);
    toolBarTop->addAction(ButtonIcon2, "Crea nuovo...");
    addToolBar(Qt::TopToolBarArea,toolBarTop);

    QPixmap pixmap4(":/images/save.png");
    QIcon ButtonIcon4(pixmap4);
    toolBarTop->addAction(ButtonIcon4, "Salva grafico corrente...");
    addToolBar(Qt::TopToolBarArea,toolBarTop);

    QPixmap pixmap5(":/images/open.png");
    QIcon ButtonIcon5(pixmap5);
    toolBarTop->addAction(ButtonIcon5, "Apri grafico da file...");
    addToolBar(Qt::TopToolBarArea,toolBarTop);

    toolBarTop->addSeparator();

    QPixmap pixmap3(":/images/pencil.png");
    QIcon ButtonIcon3(pixmap3);
    toolBarTop->addAction(ButtonIcon3, "Modifica collezione...");
    addToolBar(Qt::TopToolBarArea,toolBarTop);

    toolBarTop->addSeparator();

    QPixmap pixmap6(":/images/paint.png");
    QIcon ButtonIcon6(pixmap6);
    toolBarTop->addAction(ButtonIcon6, "Imposta schema colori...");
    addToolBar(Qt::TopToolBarArea,toolBarTop);

    this->setPalette(pal1);
    this->menuBar()->setPalette(pal2);
    this->statusBar()->setPalette(pal2);
    statusBar()->setStyleSheet("background-color: white");
}
