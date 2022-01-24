#include "charts_cartesianchart_addpoints.h"
#include <presenter_chart_view.h>
#include <charts_main_window.h>

Charts_Cartesianchart_AddPoints::Charts_Cartesianchart_AddPoints(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout();
    auto gridLayout = new QGridLayout();

    spinX = new QSpinBox();
    spinY = new QSpinBox();
    add = new QPushButton("AGGIUNGI");
    add->setCursor(Qt::CursorShape::PointingHandCursor);

    close = new QPushButton("CHIUDI");
    close->setCursor(Qt::CursorShape::PointingHandCursor);
    signalLabel = new QLabel("Valore già inserito");
    signalLabel->setStyleSheet("QLabel { background-color : transparent; color : red; }");

    auto labelX = new QLabel("Val. X");
    auto labelY = new QLabel("Val. Y");

    gridLayout->addWidget(labelX,0,0);
    gridLayout->addWidget(labelY,0,1);
    gridLayout->addWidget(add,0,2);
    gridLayout->addWidget(spinX,1,0);
    gridLayout->addWidget(spinY,1,1);
    gridLayout->addWidget(close,1,2);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(signalLabel);

    setLayout(mainLayout);
    QPalette p = QPalette();
    p.setColor(QPalette::Window, QColor(200,235,255));
    this->setPalette(p);
}

void Charts_Cartesianchart_AddPoints::set_chart_presenter(presenter_chart_view* ccw){
    c = ccw;
    connect(add, SIGNAL(clicked()), c, SLOT(add_point()));
}

void Charts_Cartesianchart_AddPoints::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}
