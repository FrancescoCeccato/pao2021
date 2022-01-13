#include "charts_comparisonchart_editor.h"

Charts_Comparisonchart_Editor::Charts_Comparisonchart_Editor(QWidget *parent)
    : QWidget{parent}
{

    auto mainLayout = new QGridLayout();

    auto label1 = new QLabel("Numero di categorie:");
    spinBox = new QSpinBox();
    spinBox->setMaximum(20);

    auto label2 = new QLabel("Inserimento valori");
    auto label3 = new QLabel("Titoli categorie");
    label3->setFixedWidth(120);
    gridValues = new QTableWidget(20,20);
    gridCategories = new QTableWidget(20,1);
    gridCategories->setFixedWidth(120);
    signalLabel = new QLabel("Eccezione fatale!");
    signalLabel->setStyleSheet("QLabel { background-color : transparent; color : red; }");
    okButton = new QPushButton("IMPOSTA");
    okButton->setCursor(Qt::CursorShape::PointingHandCursor);
    okButton->setFixedWidth(120);

    gridCategories->horizontalHeader()->hide();

    mainLayout->addWidget(label1,0,0);
    mainLayout->addWidget(spinBox,0,1);
    mainLayout->addWidget(label2,1,0);
    mainLayout->addWidget(label3,1,1);
    mainLayout->addWidget(gridValues,2,0);
    mainLayout->addWidget(gridCategories,2,1);
    mainLayout->addWidget(signalLabel,3,0);
    mainLayout->addWidget(okButton,3,1);

    setLayout(mainLayout);

    QPalette p = QPalette();
    p.setColor(QPalette::Window, QColor(200,235,255));
    this->setPalette(p);
}
