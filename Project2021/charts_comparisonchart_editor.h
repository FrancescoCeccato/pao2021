#ifndef CHARTS_COMPARISONCHART_EDITOR_H
#define CHARTS_COMPARISONCHART_EDITOR_H

#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>
#include <QHeaderView>
#include <comparison_chart.h>


class presenter_chart_view;
class Charts_Comparisonchart_Editor : public QWidget
{
    Q_OBJECT
private:
     presenter_chart_view* c;
public:
    QSpinBox *spinBox;
    QTableWidget *gridValues, *gridLabelCategories, *gridLabelEntries;
    QLabel *signalLabel, *label2, *label3, *label4;
    QPushButton *okButton;
    explicit Charts_Comparisonchart_Editor(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
    void set_grids(comparison_chart*);

};

#endif // CHARTS_COMPARISONCHART_EDITOR_H
