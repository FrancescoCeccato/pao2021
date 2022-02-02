#include <QLayout>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <vector>
#include <iostream>
#include <presenter_chart_view.h>
#include <comparison_chart.h>
#include <cartesian_chart.h>
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <polar_chart.h>
#include <time_chart.h>
#include <dot_chart.h>
#include <charts_main_window.h>


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
    valuesList->setContextMenuPolicy(Qt::CustomContextMenu);
    deleteP = new QMenu();
    deleteP->addAction(new QAction("Cancella punto", deleteP));
    connect(valuesList ,&QTreeWidget::customContextMenuRequested, this, &Charts_Main_Window::menu_delete);
    connect(valuesList ,SIGNAL(itemSelectionChanged()), this, SLOT(expand_pie_chart()));


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
    //statsList->setStyleSheet("QListWidget::item { border-bottom: 1px solid lightgray; padding: 2px; }");

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

    /*simple_bar_chart* sb = new simple_bar_chart("prova", false);
    double* d1 = new double[1] {6};
    double* d2 = new double[1] {7};
    double* d3 = new double[1] {8};
    double* d4 = new double[1] {5};
    double* d5 = new double[1] {9};
    sb->add_entry(d1, "A");
    sb->add_entry(d2, "B");
    sb->add_entry(d3, "C");
    sb->add_entry(d4, "D");
    sb->add_entry(d5, "E");
    show_charts(sb);
    time_chart t = time_chart("Test", "X", "Y");
    t.add_point(3,8);
    t.add_point(5,4);
    t.add_point(4,6);
    t.add_point(1,5);
    t.add_point(2,7);
    t.add_point(6,2);
    t.add_point(7,5);
    show_time_chart(&t);
    showParent_list_values(&t);
    pie_chart pc = pie_chart("Cibo per settimana");
    pc.add_entry(20, "Grassi");
    pc.add_entry(10, "Zuccheri");
    pc.add_entry(30, "Proteine");
    pc.add_entry(40, "Carboidrati");
    showParent_list_values(&pc);
    show_pie_chart(&p);
    stacked_bar_chart* s = new stacked_bar_chart(6, true, "Voti", false);
    double* d1 = new double[6] {6,5,8,9,6,7};
    double* d2 = new double[6] {7,4,9,7,5,7};
    double* d3 = new double[6] {8,6,8,6,7,9};
    double* d4 = new double[6] {7,8,10,10,7,8};
    double* d5 = new double[6] {8,7,9,10,8,9};
    s->add_entry(d1, "Verifica 1");
    s->add_entry(d2, "Verifica 2");
    s->add_entry(d3, "Verifica 3");
    s->add_entry(d4, "Verifica 4");
    s->add_entry(d5, "Verifica 5");
    std::vector<std::string> categories{"Jessica", "Federico", "Alessia", "Bob", "Marko","Anna"};
    s->set_categories(categories);
    show_charts(s);
    showParent_list_values(s);
    polar_chart p = polar_chart("Voti");
    p.add_entry(30, "Magia");
    p.add_entry(45, "Resistenza");
    p.add_entry(70, "Forza");
    p.add_entry(80, "Agilità");
    p.add_entry(50, "Special");
    p.add_entry(30, "Cura");
    show_polar_chart(&p);*/
    /*dot_chart* t = new dot_chart("Test", "X", "Y");
    t->add_point(3,8);
    t->add_point(5,4);
    t->add_point(4,6);
    t->add_point(1,5);
    t->add_point(2,7);
    t->add_point(6,2);
    t->add_point(7,5);
    show_dot_chart(t);
    showParent_list_values(t);*/

}

void Charts_Main_Window::set_chart_presenter(presenter_chart_view* ccw){
    c = ccw;
    connect(settings, SIGNAL(clicked()), c, SLOT(open_settings()));
    connect(deleteP->actions()[0], SIGNAL(triggered()), c, SLOT(delete_point()));
    connect(TC_Calculate, SIGNAL(clicked()), c, SLOT(give_balance()));
}

void Charts_Main_Window::set_comparison_editor(Charts_Comparisonchart_Editor* cce){
    comp_editor = cce;
}

void Charts_Main_Window::set_cartesian_editor(Charts_Cartesianchart_AddPoints* cap){
    cart_editor = cap;
}


void Charts_Main_Window::show_simple_bar_chart(chart* c){
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
              QBarSet* set = new QBarSet(QString::fromStdString(simple_bc->give_entry_label(i)));
              std::vector<double> entries_v = simple_bc->give_entry_values(i);
              *set << entries_v[0];
              QBarSeries* series = new QBarSeries();
              series->append(set);
              chart->addSeries(series);
              series->attachAxis(axisY);
              label.append(QString::fromStdString(simple_bc->give_entry_label(i)));
         }
         axisX->append(label);
         chart->addAxis(axisX, Qt::AlignBottom);
         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignLeft);
         chartView->setChart(chart);
     }else if(simple_bc && simple_bc->is_horizontal()){
         QChart* chart = new QChart();
         chart->setTitle(QString::fromStdString(simple_bc->get_title()));
         QStringList label;
         QBarCategoryAxis *axisY = new QBarCategoryAxis();
         QValueAxis *axisX = new QValueAxis();
         axisX->setRange(0, 10);
         chart->addAxis(axisX, Qt::AlignBottom);
         for(uint i = 0; i<simple_bc->get_entries_size();++i){
              QHorizontalBarSeries* series = new QHorizontalBarSeries();
              QBarSet* set = new QBarSet(QString::fromStdString(simple_bc->give_entry_label(i)));
              std::vector<double> entries_v = simple_bc->give_entry_values(i);
              *set << entries_v[0];
              series->append(set);
              chart->addSeries(series);
              label.append(QString::fromStdString(simple_bc->give_entry_label(i)));
              series->attachAxis(axisX);
         }
         axisY->append(label);
         chart->addAxis(axisY, Qt::AlignLeft);
         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignLeft);
         chartView->setChart(chart);
     }
}

void Charts_Main_Window::show_stacked_bar_chart(chart* c){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(c);
    if(stacked_bc && !stacked_bc->is_horizontal() && !stacked_bc->is_segmented()){
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
        for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
             QBarSet* set = new QBarSet(QString::fromStdString(stacked_bc->get_categories(i)));
             for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                 std::vector<double> entries_v = stacked_bc->give_entry_values(j);
                 *set << entries_v[i];
                 categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
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
    }else if(stacked_bc && stacked_bc->is_horizontal() && !stacked_bc->is_segmented()){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(stacked_bc->get_title()));
        QStringList categories;
        QBarCategoryAxis *axisY = new QBarCategoryAxis();
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, stacked_bc->get_nvalues()*10);
        axisX->setTickCount(11);
        axisX->setMinorTickCount(4);
        chart->addAxis(axisX, Qt::AlignBottom);
        QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();
        for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
             QBarSet* set = new QBarSet(QString::fromStdString(stacked_bc->get_categories(i)));
             for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                 std::vector<double> entries_v = stacked_bc->give_entry_values(j);
                 *set << entries_v[i];
                 categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
             }
             series->append(set);
        }
        chart->addSeries(series);
        series->attachAxis(axisX);
        axisY->append(categories);
        chart->addAxis(axisY, Qt::AlignLeft);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_segmented_bar_chart(chart* c){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(c);
    if(stacked_bc && !stacked_bc->is_horizontal() && stacked_bc->is_segmented()){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(stacked_bc->get_title()));
        QStringList categories;
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 100);
        axisY->setTickCount(11);
        axisY->setMinorTickCount(4);
        chart->addAxis(axisY, Qt::AlignLeft);
        QStackedBarSeries* series = new QStackedBarSeries();
        for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
             QBarSet* set = new QBarSet(QString::fromStdString(stacked_bc->get_categories(i)));
             for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                 std::vector<double> entries_v = stacked_bc->give_entry_percentages(j);
                 *set << entries_v[i];
                 categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
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
    }else if(stacked_bc && stacked_bc->is_horizontal() && stacked_bc->is_segmented()){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(stacked_bc->get_title()));
        QStringList categories;
        QBarCategoryAxis *axisY = new QBarCategoryAxis();
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, stacked_bc->get_nvalues()*10);
        axisX->setTickCount(11);
        axisX->setMinorTickCount(4);
        chart->addAxis(axisX, Qt::AlignBottom);
        QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();
        for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
             QBarSet* set = new QBarSet(QString::fromStdString(stacked_bc->get_categories(i)));
             for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                 std::vector<double> entries_v = stacked_bc->give_entry_percentages(j);
                 *set << entries_v[i]/stacked_bc->get_entries_size()*100;
                 categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
             }
             series->append(set);
        }
        chart->addSeries(series);
        series->attachAxis(axisX);
        axisY->append(categories);
        chart->addAxis(axisY, Qt::AlignLeft);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_pie_chart(chart* c){
    const pie_chart* pie_c = dynamic_cast<const pie_chart*>(c);
    if(pie_c){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(pie_c->get_title()));
        QPieSeries* series = new QPieSeries();
        for(uint i = 0; i<pie_c->get_entries_size();++i){
             QString s = QString::fromStdString(pie_c->give_entry_label(i)) + " " + QString::number(pie_c->give_slice_percentage(i)) + "%";
             series->append(s, pie_c->give_slice_percentage(i)/100);
             QPieSlice* q = series->slices().at(i);
             q->setLabelVisible();
        }
        chart->addSeries(series);
        chart->legend()->hide();
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_polar_chart(chart* c){
    const polar_chart* pol_c = dynamic_cast<const polar_chart*>(c);
    if(pol_c){
        const qreal radialMin = 0;
        const qreal radialMax = 100;
        QStringList categories;
        QPolarChart *chart = new QPolarChart();
        chart->setTitle(QString::fromStdString(pol_c->get_title()));
        QCategoryAxis *angularAxis = new QCategoryAxis();
        angularAxis->setShadesVisible(true);
        angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
        for(uint i = 0; i<pol_c->get_entries_size();++i){
             angularAxis->append(QString::fromStdString(pol_c->give_entry_label(i)),(i+1)*100/pol_c->get_entries_size());
        }
        chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);
        QValueAxis *radialAxis = new QValueAxis();
        radialAxis->setTickCount(11);
        radialAxis->setLabelFormat("%d");
        chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
        radialAxis->setRange(radialMin, radialMax);
        angularAxis->setRange(0, 100);
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_time_chart(chart* c){
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
        chart->createDefaultAxes();
        chart->legend()->hide();
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_dot_chart(chart* c){
    const dot_chart* dot_c = dynamic_cast<const dot_chart*>(c);
    if(dot_c){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(dot_c->get_title()));
        QScatterSeries* series = new QScatterSeries();
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        series->setMarkerSize(15);
        std::vector<std::pair<float,float>> points = dot_c->get_points();
        for(uint i = 0; i<dot_c->get_points_amount();++i){
            QPointF p(points[i].first, points[i].second);
            series->append(p);
        }
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0,10);
        chart->addAxis(axisX, Qt::AlignBottom);
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0, 10);
        chart->addAxis(axisY, Qt::AlignLeft);
        chart->addSeries(series);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        chart->setDropShadowEnabled(false);
        chart->legend()->hide();
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_charts(chart* c){
    show_simple_bar_chart(c);
    show_stacked_bar_chart(c);
    show_segmented_bar_chart(c);
    show_pie_chart(c);
    show_time_chart(c);
    show_dot_chart(c);
}

void Charts_Main_Window::showParent_list_values(chart* c){
    valuesList->clear();
     const comparison_chart* cp = dynamic_cast<const comparison_chart*>(c);
     if(cp){
         QPixmap p(":/images/square.png");
         QIcon iconDot(p);
         for(uint i = 0; i<cp->get_entries_size();++i){
             auto item = new QTreeWidgetItem();
             item->setText(0, QString::fromStdString(cp->give_entry_label(i)));
             item->setIcon(0,iconDot);
             showChild_list_values(item, cp, i);
             valuesList->addTopLevelItem(item);
         }
     }else{
         const cartesian_chart* cc = static_cast<cartesian_chart*>(c);
         QPixmap p(":/images/dot.png");
         QIcon iconDot(p);
         std::vector<std::pair<float,float>> points = cc->get_points();
         for(uint i = 0; i<cc->get_points_amount();++i){
             auto item = new QTreeWidgetItem();
             item->setText(0, "(" + QString::number(points[i].first) + "," + QString::number(points[i].second)+ ")");
             item->setIcon(0,iconDot);
             valuesList->addTopLevelItem(item);
         }
     }
}

void Charts_Main_Window::showChild_list_values(QTreeWidgetItem* parent, const chart* cp, uint index){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(cp);
    if(stacked_bc){
        std::vector<double> entries_v;
        stacked_bc->is_segmented() ?  entries_v = stacked_bc->give_entry_percentages(index) :
                 entries_v = stacked_bc->give_entry_values(index);
        for(uint i = 0; i<stacked_bc->get_nvalues();++i){
            auto categ = new QTreeWidgetItem();
            QString s = "";
            stacked_bc->is_segmented() ? s = QString::number(std::round(entries_v[i])) + "%" : s = QString::number(entries_v[i]);
            categ->setText(0, QString::fromStdString(stacked_bc->get_categories(i)) + ": " + s);
            parent->addChild(categ);
        }
    }
}

void Charts_Main_Window::show_chart_info(std::vector<std::string> info){
    statsList->clear();
    for(uint i = 0; i<info.size(); ++i){
        auto item = new QListWidgetItem();
        item->setText(QString::fromStdString(info[i]));
        statsList->addItem(item);
    }
}

void Charts_Main_Window::menu_delete(const QPoint & pos){
    uint sel = c->get_selected();
    if(sel == 5 || sel == 6)
        deleteP->exec(valuesList->mapToGlobal(pos));
}

void Charts_Main_Window::expand_pie_chart(){
    uint sel = c->get_selected();
    if(sel == 3){
        QTreeWidgetItem *nd = valuesList->currentItem();
        if(nd){
             uint index = valuesList->indexOfTopLevelItem(nd);
             QChart* chart = chartView->chart();
             QPieSeries* series = static_cast<QPieSeries*>(chart->series().first());
             for(int i = 0; i< series->slices().size();++i){
                 series->slices().at(i)->setExploded(false);
             }
             series->slices().at(index)->setExploded(true);
        }
    }
}














