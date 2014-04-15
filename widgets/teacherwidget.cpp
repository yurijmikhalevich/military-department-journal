#include "teacherwidget.h"
#include "qt4table-steroids/booleancomboboxdelegate.h"
#include "models/teachermodel.h"
#include <QSpacerItem>

TeacherWidget::TeacherWidget(QWidget *parent)
  : BaseWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    controlsLayout(new QHBoxLayout()),
    showDismissedCheckBox(new QCheckBox(tr("Показать уволенных"), this)),
    addTeacherButton(new QPushButton(tr("Добавить преподавателя"), this)),
    teacherName(new QLineEdit(this)) {
  model = new TeacherModel(view);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  view->setModel(model);
  view->setItemDelegateForColumn(
        1, new BooleanComboBoxDelegate(tr("Уволен"), tr("Работает"), view));
  connect(showDismissedCheckBox, SIGNAL(toggled(bool)),
          model, SLOT(showDismissed(bool)));
  teacherName->setPlaceholderText(tr("Имя нового преподавателя"));
  addTeacherButton->setEnabled(false);
  connect(teacherName, SIGNAL(returnPressed()), this, SLOT(addTeacher()));
  connect(addTeacherButton, SIGNAL(clicked()), this, SLOT(addTeacher()));
  connect(teacherName, SIGNAL(textChanged(QString)),
          this, SLOT(teacherNameChanged(QString)));
  controlsLayout->addWidget(teacherName);
  controlsLayout->addWidget(addTeacherButton);
  mainLayout->addWidget(showDismissedCheckBox);
  mainLayout->addWidget(view);
  mainLayout->addLayout(controlsLayout);
  view->setColumnWidth(1, 70);
  view->setColumnWidth(2, 230);
}

void TeacherWidget::teacherNameChanged(const QString name) {
  if (name.isEmpty()) {
    addTeacherButton->setDisabled(true);
  } else {
    addTeacherButton->setEnabled(true);
  }
}

void TeacherWidget::addTeacher() {
  QString name = teacherName->text().simplified();
  if (name.isEmpty()) {
    teacherName->setFocus();
    emit error(tr("Имя преподавателя не может быть пустым"));
    return;
  }
  QVariantMap newTeacher;
  newTeacher.insert("name", name);
  if (insertRecord(newTeacher) != -1) {
    teacherName->clear();
  }
}
