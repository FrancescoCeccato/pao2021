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
    spinBox->setMinimum(1);


    label2 = new QLabel("INSERIMENTO VALORI");
    label3 = new QLabel("NOMI CATEGORIE");
    label4 = new QLabel("TITOLI DEI RECORD");
    label3->setFixedWidth(120);
    gridValues = new QTableWidget(20,20);
    gridLabelCategories = new QTableWidget(20,1);
    gridLabelEntries = new QTableWidget(1,20);
    gridLabelCategories->setFixedWidth(120);
    gridLabelEntries->setFixedHeight(100);
    signalLabel = new QLabel("Eccezione fatale!");
    signalLabel->setStyleSheet("QLabel { background-color : transparent; color : red; }");
    okButton = new QPushButton("IMPOSTA");
    okButton->setCursor(Qt::CursorShape::PointingHandCursor);
    okButton->setFixedWidth(120);

    gridLabelCategories->horizontalHeader()->hide();
    gridLabelEntries->verticalHeader()->hide();


    mainLayout->addWidget(label1,0,0);
    mainLayout->setAlignment(label1, Qt::AlignRight);
    mainLayout->addWidget(spinBox,0,1);
    mainLayout->addWidget(label2,1,0);
    mainLayout->addWidget(label3,1,1);
    mainLayout->addWidget(gridValues,2,0);
    mainLayout->addWidget(gridLabelCategories,2,1);
    mainLayout->addWidget(gridLabelEntries,3,0);
    mainLayout->addWidget(label4,3,1);
    mainLayout->addWidget(signalLabel,4,0);
    mainLayout->addWidget(okButton,4,1);

    setLayout(mainLayout);

    QPalette p = QPalette();
    p.setColor(QPalette::Window, QColor(200,235,255));
    this->setPalette(p);

}

void Charts_Comparisonchart_Editor::set_chart_presenter(presenter_chart_view* ccw){
    c = ccw;
    connect(okButton, SIGNAL(clicked()), c, SLOT(add_entry_comparison()));
    connect(spinBox,  SIGNAL(valueChanged(int)), c, SLOT(populateRow()));
}

void Charts_Comparisonchart_Editor::set_mainchart_view(Charts_Main_Window* cmw){charts_mw = cmw;}

void Charts_Comparisonchart_Editor::set_grids(comparison_chart* cc){
    gridLabelEntries->clear();
    for(uint k = 0; k<cc->get_nvalues();++k)
         c->populateRowWithLineEdit(k);
    c->populateRowWithLineEdit(0);
    for(uint i = 0;i<cc->get_entries_size();++i){
        std::vector<double> values = cc->give_entry_values(i);
        std::string label = cc->give_entry_label(i);
        auto item = new  QTableWidgetItem();
        item->setText(QString::fromStdString(label));
        gridLabelEntries->setItem(0,i,item);
        for(uint j = 0; j<cc->get_nvalues();++j){
            static_cast<QLineEdit*>(gridValues->cellWidget(j, i))->setText(QString::number(values[j]));
        }
    }
}


