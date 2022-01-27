#include "dialog_entrance.h"

#define BTN_SIDE 200

Dialog_Entrance::Dialog_Entrance(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* main = new QVBoxLayout();
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(200,235,255));

    QHBoxLayout* container = new QHBoxLayout();
    QVBoxLayout* lLeft = new QVBoxLayout();
    lLeft->setAlignment(Qt::AlignRight);
    QVBoxLayout* lRight = new QVBoxLayout();
    lRight->setAlignment(Qt::AlignLeft);

    btnLeft = new QPushButton();
    btnLeft->setFixedSize(BTN_SIDE,BTN_SIDE);
    QPixmap pixmap1(":/images/new.png");
    QIcon ButtonIcon1(pixmap1);
    btnLeft->setIconSize(QSize(0.75*BTN_SIDE,0.75*BTN_SIDE));
    btnLeft->setIcon(ButtonIcon1);
    btnLeft->setCursor(Qt::CursorShape::PointingHandCursor);
    lblLeft1 = new QLabel("Crea");
    lblLeft1->setStyleSheet("QLabel { font-weight: bold; }");
    lblLeft1->setAlignment(Qt::AlignCenter);
    lblLeft2 = new QLabel("Crea un nuovo grafico da zero.");
    lblLeft2->setAlignment(Qt::AlignCenter);
    lLeft->addWidget(btnLeft);
    lLeft->addWidget(lblLeft1);
    lLeft->addWidget(lblLeft2);

    btnRight = new QPushButton();
    btnRight->setFixedSize(BTN_SIDE,BTN_SIDE);
    QPixmap pixmap2(":/images/open.png");
    QIcon ButtonIcon2(pixmap2);
    btnRight->setIconSize(QSize(0.75*BTN_SIDE,0.75*BTN_SIDE));
    btnRight->setIcon(ButtonIcon2);
    btnRight->setCursor(Qt::CursorShape::PointingHandCursor);
    lblRight1 = new QLabel("Apri");
    lblRight1->setStyleSheet("QLabel { font-weight: bold; }");
    lblRight1->setAlignment(Qt::AlignCenter);
    lblRight2 = new QLabel("Apri un grafico già esistente da file.");
    lblRight2->setAlignment(Qt::AlignCenter);
    lRight->addWidget(btnRight);
    lRight->addWidget(lblRight1);
    lRight->addWidget(lblRight2);

    container->addLayout(lLeft);
    container->addLayout(lRight);
    main->addLayout(container);
    this->setLayout(main);
    this->setPalette(pal);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}
