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
    label1->setStyleSheet("QLabel { font-weight: bold; }");
    spinBox = new QSpinBox();
    spinBox->setMaximum(20);

    auto label2 = new QLabel("Inserimento valori");
    auto label3 = new QLabel("Titoli categorie");
    label3->setFixedWidth(120);
    gridValues = new QTableWidget(20,20);
    gridLabelCategories = new QTableWidget(20,1);
    gridLabelEntries = new QTableWidget(1,20);

    gridLabelCategories->setFixedWidth(120);
    gridLabelEntries->setFixedHeight(65);
    signalLabel = new QLabel("Eccezione fatale!");
    signalLabel->setStyleSheet("QLabel { background-color : transparent; color : red; }");
    okButton = new QPushButton("IMPOSTA");
    okButton->setCursor(Qt::CursorShape::PointingHandCursor);
    okButton->setFixedWidth(120);
    gridLabelCategories->horizontalHeader()->hide();
    gridLabelEntries->verticalHeader()->hide();

    populateRowWithLineEdit(0);

    mainLayout->addWidget(label1,0,0);
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

void Charts_Comparisonchart_Editor::populateRowWithLineEdit(uint row) {
    for(int col = 0; col<20; col++) {
        auto line = new QLineEdit();
        line->setValidator(new QDoubleValidator());
        gridValues->setCellWidget(row,col,line);
     }
}

double Charts_Comparisonchart_Editor::getCellNumericValue(uint row, uint col) {
    return static_cast<QLineEdit*>(gridValues->cellWidget(row, col))->text().toDouble();

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
