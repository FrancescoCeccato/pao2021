#ifndef DIALOG_ENTRANCE_H
#define DIALOG_ENTRANCE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class Dialog_Entrance : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *main, *lLeft, *lRight;
    QHBoxLayout *container;
    QPushButton *btnLeft, *btnRight;
    QLabel *lblLeft1, *lblRight1,*lblLeft2, *lblRight2;

public:
    explicit Dialog_Entrance(QWidget *parent = nullptr);

signals:

};

#endif // DIALOG_ENTRANCE_H
