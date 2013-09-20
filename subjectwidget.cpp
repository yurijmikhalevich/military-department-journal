#include "subjectwidget.h"
#include "subjectmodel.h"

SubjectWidget::SubjectWidget(QWidget *parent) :
    BaseWidget(parent)
{
    model = new SubjectModel(this);
    view->setModel(model);
}
