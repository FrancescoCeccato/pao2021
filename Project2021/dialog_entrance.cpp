#include "dialog_entrance.h"
#include <presenter_chart_view.h>

#define BTN_SIDE 200

Dialog_Entrance::Dialog_Entrance(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* main = new QVBoxLayout();
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(135,235,255));

    QHBoxLayout* container = new QHBoxLayout();
    QVBoxLayout* lLeft = new QVBoxLayout();
    lLeft->setAlignment(Qt::AlignRight);
    QVBoxLayout* lRight = new QVBoxLayout();
    lRight->setAlignment(Qt::AlignLeft);

    btnNew = new QPushButton();
    btnNew->setFixedSize(BTN_SIDE,BTN_SIDE);
    QPixmap pixmap1(":/images/new.png");
    QIcon ButtonIcon1(pixmap1);
    btnNew->setIconSize(QSize(0.75*BTN_SIDE,0.75*BTN_SIDE));
    btnNew->setIcon(ButtonIcon1);
    btnNew->setCursor(Qt::CursorShape::PointingHandCursor);
    lblLeft1 = new QLabel("Crea");
    lblLeft1->setAlignment(Qt::AlignCenter);
    lblLeft2 = new QLabel("Crea un nuovo grafico da zero.");
    lblLeft2->setAlignment(Qt::AlignCenter);
    lLeft->addWidget(btnNew);
    lLeft->addWidget(lblLeft1);
    lLeft->addWidget(lblLeft2);

    btnOpen = new QPushButton();
    btnOpen->setFixedSize(BTN_SIDE,BTN_SIDE);
    QPixmap pixmap2(":/images/open.png");
    QIcon ButtonIcon2(pixmap2);
    btnOpen->setIconSize(QSize(0.75*BTN_SIDE,0.75*BTN_SIDE));
    btnOpen->setIcon(ButtonIcon2);
    btnOpen->setCursor(Qt::CursorShape::PointingHandCursor);
    lblRight1 = new QLabel("Apri");
    lblRight1->setAlignment(Qt::AlignCenter);
    lblRight2 = new QLabel("Apri un grafico già esistente da file.");
    lblRight2->setAlignment(Qt::AlignCenter);
    lRight->addWidget(btnOpen);
    lRight->addWidget(lblRight1);
    lRight->addWidget(lblRight2);

    container->addLayout(lLeft);
    container->addLayout(lRight);
    main->addLayout(container);
    this->setLayout(main);
    this->setPalette(pal);

}


void Dialog_Entrance::set_chart_presenter(presenter_chart_view *ccw){
    c = ccw;
    connect(btnNew, SIGNAL(clicked()), c, SLOT(open_new()));
    connect(btnOpen, SIGNAL(clicked()), c, SLOT(load()));
}


