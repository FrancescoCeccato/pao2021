#include "charts_comparisonchart_editor.h"
#include <presenter_chart_view.h>
#include <charts_main_window.h>
#include "iostream"
#include "vector"

Charts_Comparisonchart_Editor::Charts_Comparisonchart_Editor(QWidget *parent)
    : QWidget{parent}
{

    auto mainLayout = new QGridLayout();

    auto label1 = new QLabel("Numero di categorie:");
    spinBox = new QSpinBox();
    spinBox->setMaximum(20);


    auto label2 = new QLabel("INSERIMENTO VALORI");
    auto label3 = new QLabel("NOMI CATEGORIE");
    auto label4 = new QLabel("TITOLI DEI RECORD");
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

void Charts_Comparisonchart_Editor::set_chart_presenter(presenter_chart_view* ccw){
    c = ccw;
    connect(okButton, SIGNAL(clicked()), c, SLOT(add_entry_comparison()));
}

void Charts_Comparisonchart_Editor::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}

void Charts_Comparisonchart_Editor::set_grids(comparison_chart* c){
    for(uint i = 0;i<c->get_entries_size();++i){
        std::vector<double> values = c->give_entry_values(i);
        std::string label = c->give_entry_label(i);
        auto item = new  QTableWidgetItem();
        item->setText(QString::fromStdString(label));
        gridCategories->setItem(i,0,item);
        for(uint j = 0; j<c->get_nvalues();++j){
            auto item = new  QTableWidgetItem();
            item->setText(QString::number(values[j]));
            gridValues->setItem(j,i,item);
        }
    }
}
