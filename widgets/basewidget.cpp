#include "basewidget.h"

BaseWidget::BaseWidget(QWidget *parent) :
    QWidget(parent)
{
    view = new SteroidsView(this);
}
