#ifndef CHARTS_CARTESIANCHART_ADDPOINTS_H
#define CHARTS_CARTESIANCHART_ADDPOINTS_H

#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>

class Charts_Cartesianchart_AddPoints : public QWidget
{
    Q_OBJECT
public:
    QSpinBox *spinX, *spinY;
    QPushButton *add, *close;
    QLabel* signalLabel;
    explicit Charts_Cartesianchart_AddPoints(QWidget *parent = nullptr);

signals:

};

#endif // CHARTS_CARTESIANCHART_ADDPOINTS_H
