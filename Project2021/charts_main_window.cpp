#include <QLayout>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <vector>
#include <presenter_chart_view.h>
#include <comparison_chart.h>
#include <cartesian_chart.h>
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <charts_main_window.h>
#include <time_chart.h>


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
    prova = new QLineEdit("");
    prova->setPlaceholderText("insert chart title...");
    prova->setAlignment(Qt::AlignCenter);
    crea = new QPushButton("Crea");


    auto label1 = new QLabel("INIZIO");
    auto label2 = new QLabel("FINE");
    grid->addWidget(label1,0,0);
    grid->addWidget(label2,0,1);
    grid->addWidget(TC_SpinBox1,1,0);
    grid->addWidget(TC_SpinBox2,1,1);
    grid->addWidget(TC_Calculate,2,0);
    grid->addWidget(TC_Result,2,1);
    grid->addWidget(prova, 3,0);
    grid->addWidget(crea,3,1);
    grid->setRowStretch(0|1|2|3,1);
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
    /*time_chart t = time_chart("Test", "X", "Y");
    t.add_point(3,8);
    t.add_point(5,4);
    t.add_point(4,6);
    t.add_point(1,5);
    t.add_point(2,7);
    t.add_point(6,2);
    t.add_point(7,5);
    show_time_chart(&t);
    pie_chart p = pie_chart("Cibo per settimana");
    p.add_entry(20, "Grassi");
    p.add_entry(10, "Zuccheri");
    p.add_entry(30, "Proteine");
    p.add_entry(40, "Carboidrati");
    show_pie_chart(&p);
    stacked_bar_chart s = stacked_bar_chart(5, false, "Voti", false);
    double* d1 = new double[5] {6,5,8,9,6};
    double* d2 = new double[5] {7,4,9,7,5};
    double* d3 = new double[5] {8,6,8,6,7};
    double* d4 = new double[5] {7,8,10,10,7};
    double* d5 = new double[5] {8,7,9,10,8};
    s.add_entry(d1, "John");
    s.add_entry(d2, "Veronica");
    s.add_entry(d3, "Bob");
    s.add_entry(d4, "Alessia");
    s.add_entry(d5, "Anna");
    std::vector<std::string> categories{"Verifica 1", "Verifica 2", "Verifica 3", "Verifica 4", "Verifica 5"};
    s.set_categories(categories);
    show_stacked_bar_chart(&s);*/
    //set_text(s);
}

void Charts_Main_Window::set_text(std::string s){
    TC_Result->setText(QString::fromStdString(s));
}

void Charts_Main_Window::set_chart_presenter(presenter_chart_view* ccw){
    c = ccw;
    connect(crea, SIGNAL(clicked()), c, SLOT(add_comparison_charts()));
    connect(TC_Calculate, SIGNAL(clicked()), c, SLOT(add_entry_comparison()));
}

void Charts_Main_Window::show_simple_bar_chart(const chart* c){
     const simple_bar_chart* simple_bc = dynamic_cast<const simple_bar_chart*>(c);
     if(simple_bc && !simple_bc->is_horizontal()){
         QChart* chart = new QChart();
         chart->setTitle(QString::fromStdString(simple_bc->get_title()));
         QStringList label;
         QBarCategoryAxis *axisX = new QBarCategoryAxis();
         QValueAxis *axisY = new QValueAxis();
         axisY->setRange(0, 10);
         chart->addAxis(axisY, Qt::AlignLeft);
         for(uint i = 0; i<simple_bc->get_entries_size();++i){
              QBarSet* set = new QBarSet(QString::fromStdString(simple_bc->get_entry(i)->give_label()));
              *set << simple_bc->get_entry(i)->give_value(0);
              QBarSeries* series = new QBarSeries();
              series->append(set);
              chart->addSeries(series);
              series->attachAxis(axisY);
              label.append(QString::fromStdString(simple_bc->get_entry(i)->give_label()));
         }
         axisX->append(label);
         chart->addAxis(axisX, Qt::AlignBottom);
         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignLeft);
         chartView->setChart(chart);
     }
}

void Charts_Main_Window::show_stacked_bar_chart(const chart* c){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(c);
    if(stacked_bc && !stacked_bc->is_horizontal()){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(stacked_bc->get_title()));
        QStringList categories;
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, stacked_bc->get_nvalues()*10);
        axisY->setTickCount(11);
        axisY->setMinorTickCount(4);
        chart->addAxis(axisY, Qt::AlignLeft);
        QStackedBarSeries* series = new QStackedBarSeries();
        for(uint i = 0; i<stacked_bc->get_entries_size();++i){
             QBarSet* set = new QBarSet(QString::fromStdString(stacked_bc->get_entry(i)->give_label()));
             for(uint j = 0; j<stacked_bc->get_nvalues();++j){
                 set->append(stacked_bc->get_entry(i)->give_value(j));
                 categories.append(QString::fromStdString(stacked_bc->get_categories(j)));
             }
             series->append(set);
        }
        chart->addSeries(series);
        series->attachAxis(axisY);
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_pie_chart(const chart* c){
    const pie_chart* pie_c = dynamic_cast<const pie_chart*>(c);
    if(pie_c){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(pie_c->get_title()));
        QStringList categories;
        QPieSeries* series = new QPieSeries();
        for(uint i = 0; i<pie_c->get_entries_size();++i){
             series->append(QString::fromStdString(pie_c->get_entry(i)->give_label()), pie_c->give_slice_percentage(i)/100);
             QPieSlice* q = series->slices().at(i);
             q->setLabelVisible();
        }
        chart->addSeries(series);
        chart->legend()->hide();
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_time_chart(const chart* c){
    const time_chart* time_c = dynamic_cast<const time_chart*>(c);
    if(time_c){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(time_c->get_title()));
        QLineSeries *series = new QLineSeries();
        std::vector<std::pair<float,float>> points = time_c->get_points();
        for(uint i = 0; i<time_c->get_points_amount();++i){
            QPointF p(points[i].first, points[i].second);
            series->append(p);
        }
        chart->addSeries(series);
        /*QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
        axisX->setFormat("MMM yyyy");
        axisX->setTitleText(QString::fromStdString(time_c->get_label_x()));
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        QValueAxis *axisX = new QValueAxis;
        axisX->setLabelFormat("%i");
        axisX->setTitleText(QString::fromStdString(time_c->get_label_x()));
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);
        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%i");
        axisY->setTitleText(QString::fromStdString(time_c->get_label_y()));
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);*/
        chart->createDefaultAxes();
        chart->legend()->hide();
        chartView->setChart(chart);
    }
}



















