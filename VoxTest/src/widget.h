#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QMainWindow>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <QtGui/QResizeEvent>
#include <QtGui/QPushButton>
#include "glvoxel.h"

class Widget: public QMainWindow
{
    Q_OBJECT
public:
    Widget();
private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    GLVoxel *vw;
    QPushButton *pButtonRender;
protected:
    virtual void resizeEvent(QResizeEvent * event) override;

public slots:
    void onStartRender();
};

#endif