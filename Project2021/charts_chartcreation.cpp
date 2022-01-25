#include "charts_chartcreation.h"

Charts_ChartCreation::Charts_ChartCreation(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout();
    auto vl1 = new QVBoxLayout();
    auto vl2 = new QVBoxLayout();
    auto vlButtons = new QVBoxLayout();

    imageView = new QGraphicsView();
    auto labelTitle = new QLabel("Titolo");
    labelTitle->setStyleSheet("font-weight: bold;");
    labelTitle->setAlignment(Qt::AlignCenter);
    labelType = new QLabel("Tipologia");
    labelType->setStyleSheet("font-weight: bold;");
    labelType->setAlignment(Qt::AlignCenter);
    labelDescription = new QLabel("Descrizione grafico");
    labelDescription->setAlignment(Qt::AlignCenter);

    btnCreate = new QPushButton("CREA IL GRAFICO");
    btnCreate->setCursor(Qt::CursorShape::PointingHandCursor);
    chartTitle = new QLineEdit();
    chartTitle->setAlignment(Qt::AlignCenter);
    auto radioGroup = new QButtonGroup();
    auto groupBox = new QGroupBox("TIPOLOGIA GRAFICO");

    checkBox1 = new QCheckBox("Orientazione orizzontale");
    checkBox2 = new QCheckBox("Segmentato");
    checkBox1->setCursor(Qt::CursorShape::PointingHandCursor);
    checkBox2->setCursor(Qt::CursorShape::PointingHandCursor);

    radioGroup->addButton(b1= new QRadioButton("Grafico a barre (semplice)"));
    radioGroup->addButton(b2= new QRadioButton("Grafico a barre (multi-categoria)"));
    radioGroup->addButton(b3= new QRadioButton("Grafico a torta"));
    radioGroup->addButton(b4= new QRadioButton("Diagramma di Kiviat (o grafico radar)"));
    radioGroup->addButton(b5= new QRadioButton("Diagramma a punti"));
    radioGroup->addButton(b6= new QRadioButton("Grafico di evoluzione lineare"));
    auto label1 = new QLabel("GRAFICI A CATEGORIE");
    label1->setStyleSheet("font-weight: bold;");
    vlButtons->addWidget(label1);
    vlButtons->addWidget(b1);
    vlButtons->addWidget(b2);
    vlButtons->addWidget(b3);
    vlButtons->addWidget(b4);
    auto label2 = new QLabel("GRAFICI CARTESIANI");
    label2->setStyleSheet("font-weight: bold;");
    vlButtons->addWidget(label2);
    vlButtons->addWidget(b5);
    vlButtons->addWidget(b6);

    b1->setCursor(Qt::CursorShape::PointingHandCursor);
    b2->setCursor(Qt::CursorShape::PointingHandCursor);
    b3->setCursor(Qt::CursorShape::PointingHandCursor);
    b4->setCursor(Qt::CursorShape::PointingHandCursor);
    b5->setCursor(Qt::CursorShape::PointingHandCursor);
    b6->setCursor(Qt::CursorShape::PointingHandCursor);

    vl1->addWidget(labelTitle);
    vl1->addWidget(chartTitle);
    vl1->addWidget(imageView);
    vl1->addWidget(labelType);
    vl1->addWidget(labelDescription);
    vl1->addWidget(btnCreate);
    groupBox->setLayout(vlButtons);

    vl2->addWidget(checkBox1);
    vl2->addWidget(checkBox2);

    mainLayout->addLayout(vl1);
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(vl2);
    this->setLayout(mainLayout);
    QPalette p = QPalette();
    p.setColor(QPalette::Window, QColor(200,235,255));
    this->setPalette(p);
}
