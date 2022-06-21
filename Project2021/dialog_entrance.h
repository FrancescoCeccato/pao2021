#ifndef DIALOG_ENTRANCE_H
#define DIALOG_ENTRANCE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>


class presenter_chart_view;

class Dialog_Entrance : public QWidget
{
    Q_OBJECT
private:
    presenter_chart_view* c;

public: 
    QPushButton *btnNew, *btnOpen;
    QLabel *lblLeft1, *lblRight1,*lblLeft2, *lblRight2;
    explicit Dialog_Entrance(QWidget *parent = nullptr);
    void set_chart_presenter(presenter_chart_view* ccw);
};

#endif // DIALOG_ENTRANCE_H
