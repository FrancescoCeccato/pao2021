#ifndef CHARTS_PRESENTER_H
#define CHARTS_PRESENTER_H

#include <QObject>
#include "charts_main_window.h"

class Presenter : public QObject
{
    Q_OBJECT
public:
    explicit Presenter(QObject *parent = nullptr);

signals:

};

#endif // CHARTS_PRESENTER_H
