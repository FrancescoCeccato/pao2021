#include "charts_cartesianchart_addpoints.h"

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

    this->setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
}
