#ifndef CHARTS_COMPARISONCHART_EDITOR_H
#define CHARTS_COMPARISONCHART_EDITOR_H

#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QWidget>
#include <QHeaderView>

class Charts_Comparisonchart_Editor : public QWidget
{
    Q_OBJECT
public:
    QSpinBox *spinBox;
    QTableWidget *gridValues, *gridCategories;
    QLabel *signalLabel;
    QPushButton *okButton;
    explicit Charts_Comparisonchart_Editor(QWidget *parent = nullptr);

signals:

};

#endif // CHARTS_COMPARISONCHART_EDITOR_H
