#include <QCompleter>
#include <QStringList>
#include <QAbstractTableModel>
#include <QTableView>
#include "CC.h"

#ifndef CCLINEEDIT_P_H
#define CCLINEEDIT_P_H

class CCTableModel;
class CCTableView;

class CategoricalCompleter : public QCompleter {
    Q_OBJECT
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
    //  QStringList splitPath(const QString &path) const;
    //  QString pathFromIndex(const QModelIndex &index) const;
    static QStringList join(CompletionCase&,QString prefix="");
public slots:
    void verifyPrefix();
};

class CCTableModel : public QAbstractTableModel {
    Q_OBJECT
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
    Q_OBJECT
    CompletionCase* _data;
    QAbstractItemModel* origModel;
    CategoricalCompleter* completer;
    CCLineEdit* _le;
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

public slots:
    void updateSuggestions();
    void setColumnHeaders(QStringList columnHeaders);
    void setCompleter(CategoricalCompleter* completer);
    void setData(CompletionCase* data,QString prefix="");
    void setLineEdit(CCLineEdit* le) { _le=le;}
};

#endif // CCLINEEDIT_P_H
