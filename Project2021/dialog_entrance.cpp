#include "dialog_entrance.h"
#include "ui_dialog_entrance.h"

Dialog_Entrance::Dialog_Entrance(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dialog_Entrance)
{
    ui->setupUi(this);
    /*
    QStatusBar *bar = new QStatusBar(this);
    ui->*/
}

Dialog_Entrance::~Dialog_Entrance()
{
    delete ui;
}
