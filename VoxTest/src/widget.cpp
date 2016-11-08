#include "widget.h"

Widget::Widget()
{
    this->resize(800, 727);

    centralWidget = new QWidget( this );

    vw = new GLVoxel(this);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(vw);
    centralWidget->setLayout(mainLayout);
    this->setCentralWidget( centralWidget );

    pButtonRender = new QPushButton(centralWidget);
    pButtonRender->setText(QString("Start render"));
    mainLayout->addWidget(pButtonRender);

    connect( pButtonRender, SIGNAL(clicked()), vw, SLOT(StartRender()) );
}

void Widget::resizeEvent(QResizeEvent * event)
{
    
}

void Widget::onStartRender()
{
}