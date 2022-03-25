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
class Charts_Main_Window;

class Charts_Comparisonchart_Editor : public QWidget
{
    Q_OBJECT
private:
    void populateRowWithLineEdit(uint index);
    double getCellNumericValue(uint row, uint col);
public:
    presenter_chart_view* c;
    Charts_Main_Window* charts_mw;
    QSpinBox *spinBox;
    QTableWidget *gridValues, *gridLabelCategories, *gridLabelEntries;
    QLabel *signalLabel;
    QPushButton *okButton;
    explicit Charts_Comparisonchart_Editor(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
    void set_mainchart_view(Charts_Main_Window* cmw);
    void set_grids(comparison_chart*);

signals:

};

#endif // CHARTS_COMPARISONCHART_EDITOR_H
