#include <QLayout>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QtMath>
#include <vector>
#include <charts_main_window.h>
#include <presenter_chart_view.h>
#include <comparison_chart.h>
#include <cartesian_chart.h>
#include <simple_bar_chart.h>
#include <stacked_bar_chart.h>
#include <pie_chart.h>
#include <polar_chart.h>
#include <time_chart.h>
#include <dot_chart.h>


#define BTN_SIDE 100

Charts_Main_Window::Charts_Main_Window(QWidget *parent)
    : QMainWindow{parent}
{
    this->statusBar()->showMessage("");
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

    QDockWidget* dock4 = new QDockWidget("CALCOLO BILANCIO",this);
    dock4->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock4->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    auto grid = new QGridLayout();
    TC_SpinBox1 = new QSpinBox();
    TC_SpinBox2 = new QSpinBox();
    TC_SpinBox1->setMaximum(5000);
    TC_SpinBox2->setMaximum(5000);
    TC_SpinBox1->setMinimum(-5000);
    TC_SpinBox2->setMinimum(-5000);
    TC_Calculate = new QPushButton("CALCOLA");
    TC_Result = new QLabel("");
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

    toolBarTop = new QToolBar();
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

    this->setPalette(pal1);
    this->menuBar()->setPalette(pal2);
    this->statusBar()->setPalette(pal2);
    statusBar()->setStyleSheet("background-color: white");



}

void Charts_Main_Window::set_chart_presenter(presenter_chart_view* ccw){
    c = ccw;
    connect(settings, SIGNAL(clicked()), c, SLOT(open_settings()));
    connect(deleteP->actions().at(0), SIGNAL(triggered()), c, SLOT(delete_point()));
    connect(TC_Calculate, SIGNAL(clicked()), c, SLOT(give_balance()));
    connect(toolBarTop->actions().at(0), SIGNAL(triggered()), c,
                        SLOT(open_new()));
    connect(toolBarTop->actions().at(1), SIGNAL(triggered()), c,
                        SLOT(save()));
    connect(toolBarTop->actions().at(2), SIGNAL(triggered()), c,
                        SLOT(load()));
    connect(toolBarTop->actions().at(4), SIGNAL(triggered()), c,
                        SLOT(open_settings()));
}

void Charts_Main_Window::show_simple_bar_chart(chart* c){
     const simple_bar_chart* simple_bc = dynamic_cast<const simple_bar_chart*>(c);
     if(simple_bc){
         QChart* chart = new QChart();
         chart->setTitle(QString::fromStdString(simple_bc->get_title()));
         QStringList label;
         QBarCategoryAxis *axis1 = new QBarCategoryAxis();
         QValueAxis *axis2 = new QValueAxis();
         axis2->setRange(0, simple_bc->max()+10);
         if(!simple_bc->is_horizontal())
             chart->addAxis(axis2, Qt::AlignLeft);
         else
             chart->addAxis(axis2, Qt::AlignBottom);
         for(uint i = 0; i<simple_bc->get_entries_size();++i){
              QBarSet* set = new QBarSet(QString::fromStdString(simple_bc->give_entry_label(i)));
              std::vector<double> entries_v = simple_bc->give_entry_values(i);
              *set << entries_v[0];
              if(!simple_bc->is_horizontal()){
                  QBarSeries* series = new QBarSeries();
                  series->append(set);
                  chart->addSeries(series);
                  series->attachAxis(axis2);
              }
              else{
                  QHorizontalBarSeries* series = new QHorizontalBarSeries();
                  series->append(set);
                  chart->addSeries(series);
                  series->attachAxis(axis2);
              }
              label.append(QString::fromStdString(simple_bc->give_entry_label(i)));            
         }
         axis1->append(label);
         if(!simple_bc->is_horizontal())
             chart->addAxis(axis1, Qt::AlignBottom);
         else
             chart->addAxis(axis1, Qt::AlignLeft);
         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignLeft);
         chartView->setChart(chart);      
     }
}

void Charts_Main_Window::show_stacked_bar_chart(chart* c){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(c);
    if(stacked_bc && !stacked_bc->is_segmented()){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(stacked_bc->get_title()));
        QStringList categories;
        std::vector<std::string> cat = stacked_bc->get_categories();
        QBarCategoryAxis *axis1 = new QBarCategoryAxis();
        QValueAxis *axis2 = new QValueAxis();
        axis2->setRange(0, stacked_bc->max().first+10);
        axis2->setTickCount(11);
        axis2->setMinorTickCount(4);
        if(!stacked_bc->is_horizontal()){
            QStackedBarSeries* series = new QStackedBarSeries();
            chart->addAxis(axis2, Qt::AlignLeft);
            for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
                QBarSet* set = new QBarSet(QString::fromStdString(cat[i]));
                for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                     std::vector<double> entries_v = stacked_bc->give_entry_values(j);
                     *set << entries_v[i];
                     categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
                }
                series->append(set);
            }
            chart->addSeries(series);
            series->attachAxis(axis2);
        }
        else if(stacked_bc->is_horizontal()){
        QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();
        chart->addAxis(axis2, Qt::AlignBottom);
        for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
            QBarSet* set = new QBarSet(QString::fromStdString(cat[i]));
            for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                std::vector<double> entries_v = stacked_bc->give_entry_values(j);
                *set << entries_v[i];
                categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
            }
            series->append(set);
        }
        chart->addSeries(series);
        series->attachAxis(axis2);
        }
        axis1->append(categories);
        if(!stacked_bc->is_horizontal())
            chart->addAxis(axis1, Qt::AlignBottom);
        else if(stacked_bc->is_horizontal())
            chart->addAxis(axis1, Qt::AlignLeft);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_segmented_bar_chart(chart* c){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(c);
    if(stacked_bc && stacked_bc->is_segmented()){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(stacked_bc->get_title()));
        QStringList categories;
        std::vector<std::string> cat = stacked_bc->get_categories();
        QBarCategoryAxis *axis1 = new QBarCategoryAxis();
        QValueAxis *axis2 = new QValueAxis();
        axis2->setRange(0, 100);
        axis2->setTickCount(11);
        axis2->setMinorTickCount(4);
        if(!stacked_bc->is_horizontal()){
            QStackedBarSeries* series = new QStackedBarSeries();
            chart->addAxis(axis2, Qt::AlignLeft);
            for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
                 QBarSet* set = new QBarSet(QString::fromStdString(cat[i]));
                 for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                     std::vector<double> entries_v = stacked_bc->give_entry_percentages(j);
                     *set << entries_v[i];
                     categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
                 }
                 series->append(set);
            }
            chart->addSeries(series);
            series->attachAxis(axis2);
        }
        else if(stacked_bc->is_horizontal()){
            QHorizontalStackedBarSeries* series = new QHorizontalStackedBarSeries();
            chart->addAxis(axis2, Qt::AlignBottom);
            for(uint i = 0; i<stacked_bc->get_nvalues() && stacked_bc->get_entries_size() > 0;++i){
                 QBarSet* set = new QBarSet(QString::fromStdString(cat[i]));
                 for(uint j = 0; j<stacked_bc->get_entries_size();++j){
                     std::vector<double> entries_v = stacked_bc->give_entry_percentages(j);
                     *set << entries_v[i];
                     categories.append(QString::fromStdString(stacked_bc->give_entry_label(j)));
                 }
                 series->append(set);
            }
            chart->addSeries(series);
            series->attachAxis(axis2);
        }
        axis1->append(categories);
        if(!stacked_bc->is_horizontal())
            chart->addAxis(axis1, Qt::AlignBottom);
        else if(stacked_bc->is_horizontal())
            chart->addAxis(axis1, Qt::AlignLeft);
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
        QPolarChart* chart = new QPolarChart();
        //series
        QLineSeries* center = new QLineSeries();
        QLineSeries* base_line = new QLineSeries();
        QLineSeries* draw_line = new QLineSeries();
        QAreaSeries* base_area = new QAreaSeries();
        QAreaSeries* draw_area = new QAreaSeries();
        //axis
        QCategoryAxis* angularAxis = new QCategoryAxis();
        QValueAxis* radialAxis = new QValueAxis();
        qreal radialMin = 0;
        qreal radialMax = pol_c->find_max().first;
        QColor baseAreaColor = QColor(Qt::transparent);
        QColor drawAreaColor = QColor(66, 66, 255, 100);
        QColor baseLineColor = Qt::darkMagenta;
        QColor drawLineColor = Qt::darkBlue;

        QColor angularGridLineColor = Qt::black;
        QColor angularSideLineColor = Qt::transparent;
        QColor radialLineColor = Qt::transparent;
        QColor radiusLineColor = Qt::black;
        const qreal angularMin = 0;
        const qreal angularMax = 360;
        //center
        center->append(angularMin, radialMin);
        center->setBrush(Qt::NoBrush);
        center->setPen(Qt::NoPen);
        center->setPointLabelsVisible();
        center->setPointLabelsColor(Qt::red);
        center->setPointLabelsFormat(QLatin1String { "@yPoint" });
        //area
        base_area->setLowerSeries(center);
        base_area->setUpperSeries(base_line);
        draw_area->setLowerSeries(center);
        draw_area->setUpperSeries(draw_line);
        uint count = pol_c->get_entries_size();
        const auto offset = ( angularMax - angularMin ) / count;
        std::vector<double> entries_v;
        for(uint i = 0; i<count;++i){
            entries_v = pol_c->give_entry_values(i);
            base_line->append(angularMin + offset * i, radialMax);
            draw_line->append(
                angularMin + offset * i,
                radialMin + entries_v[0]
            );
            angularAxis->append(QString::fromStdString(pol_c->give_entry_label(i)), angularMin + offset * i);
        }
        if (count)
        {
            entries_v = pol_c->give_entry_values(0);
            draw_line->append(
                angularMin + offset * count,
                radialMin + entries_v[0]
            );
        }
        chart->addSeries(base_line);
        chart->addSeries(draw_line);
        chart->addSeries(base_area);
        chart->addSeries(draw_area);
        chart->addSeries(center);
        base_area->setColor(baseAreaColor);
        draw_area->setColor(drawAreaColor);
        draw_line->setBrush(Qt::NoBrush);
        draw_line->setPen(Qt::NoPen);
        draw_area->setBorderColor(drawLineColor);
        base_line->setBrush(Qt::NoBrush);
        base_line->setPen(Qt::NoPen);
        base_area->setBorderColor(baseLineColor);
        angularAxis->setGridLineColor(angularGridLineColor);
        angularAxis->setLinePenColor(angularSideLineColor);
        angularAxis->setRange(angularMin, angularMax);
        angularAxis->setStartValue(angularMin);
        angularAxis->setLabelsPosition(
            QtCharts::QCategoryAxis::AxisLabelsPositionOnValue);
        chart->addAxis(angularAxis, QtCharts::QPolarChart::PolarOrientationAngular);
        radialAxis->setGridLineColor(radialLineColor);
        radialAxis->setLinePenColor(radiusLineColor);
        radialAxis->setRange(radialMin, radialMax);
        chart->addAxis(radialAxis, QtCharts::QPolarChart::PolarOrientationRadial);
        center->attachAxis(radialAxis);
        center->attachAxis(angularAxis);
        base_line->attachAxis(radialAxis);
        base_line->attachAxis(angularAxis);
        base_area->attachAxis(radialAxis);
        base_area->attachAxis(angularAxis);
        draw_line->attachAxis(radialAxis);
        draw_line->attachAxis(angularAxis);
        draw_area->attachAxis(radialAxis);
        draw_area->attachAxis(angularAxis);
        chart->legend()->hide();
        center->hide();
        chart->layout()->setContentsMargins(0, 0, 0, 0);
        chart->setBackgroundRoundness(0);
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_time_chart(chart* c){
    const time_chart* time_c = dynamic_cast<const time_chart*>(c);
    if(time_c){
        QChart* chart = new QChart();
        chart->setTitle(QString::fromStdString(time_c->get_title()));
        QLineSeries *series = new QLineSeries();
        QLineSeries* mean = new QLineSeries();
        mean->setColor(QColor("red"));
        std::vector<std::pair<float,float>> points = time_c->get_points();
        for(uint i = 0; i<time_c->get_points_amount();++i){
            QPointF p(points[i].first, points[i].second);
            QPointF p_mean(points[i].first,time_c->average());
            series->append(p);
            mean->append(p_mean);
        }
        chart->addSeries(series);
        chart->addSeries(mean);
        chart->createDefaultAxes();
        QList<QAbstractAxis*> axis = chart->axes();
        axis[0]->setTitleText(QString::fromStdString(time_c->get_label_x()));
        axis[1]->setTitleText(QString::fromStdString(time_c->get_label_y()));
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
        chart->addSeries(series);
        chart->createDefaultAxes();
        QList<QAbstractAxis*> axis = chart->axes();
        axis[0]->setTitleText(QString::fromStdString(dot_c->get_label_x()));
        axis[1]->setTitleText(QString::fromStdString(dot_c->get_label_y()));
        if(points.size()!=0){
            std::pair<float,float> minmax_x(std::minmax_element(points.begin(),points.end()).first->first, std::minmax_element(points.begin(),points.end()).second->first);
            std::pair<float,float> minmax_y(std::minmax_element(points.begin(),points.end(),
                                                      [](const std::pair<float, float>& p1, const std::pair<float, float>& p2) {
                                                       return p1.second < p2.second; }).first->second,
                                            std::minmax_element(points.begin(),points.end(),
                                                      [](const std::pair<float, float>& p1, const std::pair<float, float>& p2) {
                                                      return p1.second < p2.second; }).second->second);
            axis[0]->setRange(minmax_x.first-5,minmax_x.second+5);
            axis[1]->setRange(minmax_y.first-5,minmax_y.second+5);
        }
        chart->setDropShadowEnabled(false);
        chart->legend()->hide();
        chartView->setChart(chart);
    }
}

void Charts_Main_Window::show_charts(chart* c){
    show_simple_bar_chart(c);
    show_stacked_bar_chart(c);
    show_segmented_bar_chart(c);
    show_polar_chart(c);
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
         if(cc){
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
}

void Charts_Main_Window::showChild_list_values(QTreeWidgetItem* parent, const chart* cp, uint index){
    const stacked_bar_chart* stacked_bc = dynamic_cast<const stacked_bar_chart*>(cp);
    if(stacked_bc){
        std::vector<double> entries_v;
        stacked_bc->is_segmented() ?  entries_v = stacked_bc->give_entry_percentages(index) :
                 entries_v = stacked_bc->give_entry_values(index);
        std::vector<std::string> cat = stacked_bc->get_categories();
        for(uint i = 0; i<stacked_bc->get_nvalues();++i){
            auto categ = new QTreeWidgetItem();
            QString s = "";
            stacked_bc->is_segmented() ? s = QString::number(std::round(entries_v[i])) + "%" : s = QString::number(entries_v[i]);
            categ->setText(0, QString::fromStdString(cat[i]) + ": " + s);
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
    uint sel = presenter_chart_view::type;
    if(sel == 5 || sel == 6)
        deleteP->exec(valuesList->mapToGlobal(pos));
}

void Charts_Main_Window::expand_pie_chart(){
    if(presenter_chart_view::type == 3){
        QTreeWidgetItem *nd = valuesList->currentItem();
        if(nd){
             uint index = valuesList->indexOfTopLevelItem(nd);
             QChart* chart = chartView->chart();
             QList<QAbstractSeries*> s = chart->series();
             QPieSeries* series = static_cast<QPieSeries*>(s.first());
             for(int i = 0; i< series->slices().size();++i){
                 series->slices().at(i)->setExploded(false);
             }
             series->slices().at(index)->setExploded(true);
        }
    }
}

void Charts_Main_Window::closeEvent(QCloseEvent *event){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Stai chiudendo il programma.");
    msgBox.setInformativeText("Vuoi salvare le modifiche del grafico corrente?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
          c->close(true);
          event->accept();
          break;
      case QMessageBox::Close:
          c->close(false);
          event->accept();
          break;
      case QMessageBox::Cancel:
          event->ignore();
          break;
      default:
          break;
    }

}













