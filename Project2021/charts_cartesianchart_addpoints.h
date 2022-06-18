#ifndef CHARTS_CARTESIANCHART_ADDPOINTS_H
#define CHARTS_CARTESIANCHART_ADDPOINTS_H

#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

class presenter_chart_view;

class Charts_Cartesianchart_AddPoints : public QWidget
{
    Q_OBJECT
private:
    presenter_chart_view* c;
public:
    QSpinBox *spinX, *spinY;
    QPushButton *add;
    QLabel* signalLabel;
    explicit Charts_Cartesianchart_AddPoints(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
};

#endif // CHARTS_CARTESIANCHART_ADDPOINTS_H
