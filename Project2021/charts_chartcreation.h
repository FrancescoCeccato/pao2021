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

class Charts_ChartCreation : public QWidget
{
    Q_OBJECT
public:
    QGraphicsView *imageView;
    QLabel *labelType, *labelDescription;
    QPushButton *btnCreate;
    QLineEdit *chartTitle;
    QCheckBox *checkBox1, *checkBox2;
    QRadioButton *b1, *b2, *b3, *b4, *b5, *b6;
    explicit Charts_ChartCreation(QWidget *parent = nullptr);


signals:

};

#endif // CHARTS_CHARTCREATION_H
