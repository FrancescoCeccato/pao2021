#ifndef DIALOG_ENTRANCE_H
#define DIALOG_ENTRANCE_H

#include <QMainWindow>

namespace Ui {
class Dialog_Entrance;
}

class Dialog_Entrance : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dialog_Entrance(QWidget *parent = nullptr);
    ~Dialog_Entrance();

private:
    Ui::Dialog_Entrance *ui;
};

#endif // DIALOG_ENTRANCE_H
