#ifndef CHARTS_CARTESIANCHART_ADDPOINTS_H
#define CHARTS_CARTESIANCHART_ADDPOINTS_H

#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

class presenter_chart_view;
class Charts_Main_Window;

class Charts_Cartesianchart_AddPoints : public QWidget
{
    Q_OBJECT
private:
    presenter_chart_view* c;
    Charts_Main_Window* charts_mw;
public:
    QSpinBox *spinX, *spinY;
    QPushButton *add, *close;
    QLabel* signalLabel;
    explicit Charts_Cartesianchart_AddPoints(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
    void set_mainchart_view(Charts_Main_Window* cmw);


signals:

};

#endif // CHARTS_CARTESIANCHART_ADDPOINTS_H
