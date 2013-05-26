#ifndef ACLINEEDIT_H
#define ACLINEEDIT_H

#include <QtGui/QLineEdit>
#include <QStringList>
#include <QTableWidget>
#include <QHeaderView>
#include <QCompleter>

class CCTableModel;
class CCTableView;

class Category : public QStringList {
    QString _title;
public:
    Category(QString title) : QStringList(), _title(title) { }
    Category(QString title, QString i) : QStringList(i), _title(title) { }
    Category(QString title, QStringList l) : QStringList(l), _title(title) { }
    const QString& title() { return _title; }
};

class CompletionCase : public QList<Category> {
    QString _prefix;
public:
    /*
     * The prefix "!\[" means this completion case is valid in all instances of [
     * which are not preceeded by a \.
     */
    CompletionCase(QString prefix) : QList<Category>(), _prefix(prefix) { }
    CompletionCase(QString prefix,QList<Category> l) : QList<Category>(l), _prefix(prefix) { }
    const QString& prefix() { return _prefix; }
};

class CategoricalCompleter : public QCompleter {
  Q_OBJECT;
  CCTableView* _tableView;
  QList<CompletionCase>& _data;
  CompletionCase* _currentSubset;
  QString _completed;
public:
  friend class CCLineEdit;
  /**
   * Creates an autocompleter for child.
   *
   * Each QStringList inside "data" represents a column.
   * The first element of each column is the column title (category)
   * The remaining elements are items under that category.
   *
   * CategoricalCompleter does not take ownership of data.
   */
  CategoricalCompleter(QLineEdit* lineEdit, QList<CompletionCase>* data);
  ~CategoricalCompleter();

protected:
  bool eventFilter(QObject *o, QEvent *e);
  QStringList splitPath(const QString &path) const;
  QString pathFromIndex(const QModelIndex &index) const;
  static QStringList join(CompletionCase&,QString prefix="");
public slots:
  void updateCurrentSuggestions();
};

class CCLineEdit : public QLineEdit {
    Q_OBJECT;
    CategoricalCompleter* _cc;
public:
    CCLineEdit(QList<CompletionCase>* data,QWidget*p=0) :
        QLineEdit(p), _cc(new CategoricalCompleter(this,data) ) { init(); }

    CCLineEdit(QList<CompletionCase>* data,const QString&s,QWidget*p=0) :
        QLineEdit(s,p), _cc(new CategoricalCompleter(this,data)) { init(); }

protected:
    void keyPressEvent(QKeyEvent *);
    void init();
};


class CCTableModel : public QAbstractTableModel {
  Q_OBJECT;
  QList<QStringList> _visibleData;
public:
  explicit CCTableModel(const QList<QStringList>& visibleData) : _visibleData(visibleData)
  {

  }

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
};

class CCTableView : public QTableView {
  Q_OBJECT;
  CompletionCase* _data;
  QAbstractItemModel* origModel;
  CategoricalCompleter* completer;
  QString _prefix;

public:
  friend class CCLineEdit;
  friend class CategoricalCompleter;

  CCTableView(CompletionCase* _data);
  const QString& prefix() { return _prefix; }

protected:
  void keyPressEvent(QKeyEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void showEvent(QShowEvent *);
  void hideEvent(QHideEvent *);
//  void indexAt(const QPoint &p) const;

public slots:
  void updateSuggestions();
  void setColumnHeaders(QStringList columnHeaders);
  void setCompleter(CategoricalCompleter* completer);
  void setData(CompletionCase* data,QString prefix="");
};


#endif // ACLINEEDIT_H
