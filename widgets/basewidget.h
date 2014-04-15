#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantMap>
#include "qt4table-steroids/steroidsview.h"

/**
 * @brief The BaseWidget class, base widget for all application tabs, describes
 * model, view and error and queryChanged interfaces
 */
class BaseWidget : public QWidget {
  Q_OBJECT
public:
  /**
   * @brief BaseWidget Constructor, initializes view
   * @param parent
   */
  explicit BaseWidget(QWidget *parent = 0);
  ~BaseWidget();
protected:
  /**
   * @brief insertRecord Inserts record into database
   * @param record Describes record
   * @return true if insert performed successfully, otherwise returns false and
   * emits error signal
   */
  int insertRecord(const QVariantMap record);
  /**
   * @brief model Pointer to widgets table model, which should be an instance of
   * QSqlTableModel
   */
  QSqlTableModel *model;
  /**
   * @brief view Pointer to widgets table view, which should be an instance of
   * SteroidsView
   */
  SteroidsView *view;
signals:
  /**
   * @brief error Signal, which informs parent class, that something went wrong
   * @param message Human readable error description
   */
  void error(QString message);
  /**
   * @brief queryChanged Signal, which called, when parent class change query,
   * used to inform model about query change
   * @param query User inputted query
   */
  void queryChanged(QString query);
  void recordInserted(int id, QVariantMap record);
protected:
  bool execQuery(QSqlQuery &query, QString errorMessage = "");
  bool execAndNextQuery(QSqlQuery &query, QString errorMessage = "");
private:
  /**
   * @brief query Common (for all tab widgets) QSqlQuery object. It is OK,
   * because application is single thread
   */
  static QSqlQuery *query;
};

#endif // BASEWIDGET_H
