#ifndef CHARTS_CHARTCREATION_H
#define CHARTS_CHARTCREATION_H

#include <QWidget>
#include <QGraphicsView>
#include <QButtonGroup>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>

class presenter_chart_view;

class Charts_ChartCreation : public QWidget
{
    Q_OBJECT
public:
     presenter_chart_view* c;
     QGraphicsView *imageView;
     QGraphicsScene *scene;
     QLabel *labelType, *labelDescription;
     QPushButton *btnCreate;
     QLineEdit *chartTitle;
     QCheckBox *checkBox1, *checkBox2;
     QRadioButton *b1, *b2, *b3, *b4, *b5, *b6;
public:
     uint selected;
     explicit Charts_ChartCreation(QWidget *parent = nullptr);
     void set_chart_presenter(presenter_chart_view* ccw);


signals:

public slots:
     void set_chart();

};

#endif // CHARTS_CHARTCREATION_H
