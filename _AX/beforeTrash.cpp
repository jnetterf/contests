#include "CCompleter.h"
#include <QCompleter>
#include <QAbstractItemView>
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QScrollBar>

// CategoricalCompleter
CategoricalCompleter::CategoricalCompleter(QLineEdit *lineEdit, QList<CompletionCase> *data) : QCompleter(join((*data)[0])),
    _tableView(new CCTableView(&(*data)[0])), _data(*data), _currentSubset(&(*data)[0])
{

    //// From http://bugreports.qt.nokia.com/browse/QTBUG-3414, substring completion
    //  setCompletionMode(QCompleter::UnfilteredPopupCompletion); // always show all completions
    //  QSortFilterProxyModel *pFilterModel = new QSortFilterProxyModel(lineEdit);
    //  pFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    //  pFilterModel->setSourceModel(lineEdit->model());
    //  connect(lineEdit, SIGNAL(textChanged(const QString &)), pFilterModel, SLOT(setFilterFixedString(const QString &)));
    //  setModel(pFilterModel); // use the filtered proxy model to do the substring matching

    setPopup(_tableView);
    lineEdit->setCompleter(this);
    _tableView->setCompleter(this);
    _tableView->updateSuggestions();
    setCompletionMode(PopupCompletion);
    connect(lineEdit,SIGNAL(textChanged(QString)),_tableView,SLOT(updateSuggestions()));
    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(updateCurrentSuggestions()));
    connect(lineEdit,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(updateCurrentSuggestions()));
}

bool CategoricalCompleter::eventFilter(QObject *o, QEvent *e)
{
    if(e->type()!=QEvent::KeyPress) {
//    if(1) {
        return QCompleter::eventFilter(o,e);
    } else {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        int columnBefore=_tableView->currentIndex().column();
        _tableView->keyPressEvent(ke);
        int columnAfter=_tableView->currentIndex().column();
        int key=ke->key();
        if((key!=Qt::Key_Up)&&(key!=Qt::Key_Down&&key!=Qt::Key_PageDown&&key!=Qt::Key_PageUp)||_tableView->isHidden()) {
            if(((key!=Qt::Key_Left)&&(key!=Qt::Key_Right))||(columnBefore==columnAfter))
            {
                (static_cast<QObject *>(widget()))->event(ke);
            }
        }
        switch (key) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Tab:
        if(_tableView->currentIndex().row()!=-1&&_tableView->currentIndex().column()!=-1)
        {
            QLineEdit*le=dynamic_cast<QLineEdit*>(widget());
            if(le) {
                QString x=_tableView->prefix();
                x.chop(_currentSubset->prefix().size());
                le->setText(x+_tableView->currentIndex().model()->data(_tableView->currentIndex()).toString());
                _completed=le->text();
            }
//            _tableView->hide();
        }
            break;

        case Qt::Key_Backtab:
        case Qt::Key_Escape:
//            _tableView->hide();
            break;

        case Qt::Key_Backspace:
        {
            QLineEdit*le=dynamic_cast<QLineEdit*>(widget());
            if(le) {
                if(_completed.size()>=le->text().size()) {
                    _completed=le->text();
                }
            }
        }
            break;
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_PageDown:
        case Qt::Key_PageUp:
        {
            QLineEdit*le=dynamic_cast<QLineEdit*>(widget());
            if(le) {
                _completed.truncate(le->cursorPosition());
            }
        }
            break;

        default:
            break;
        }

        updateCurrentSuggestions();
        return 1;
    }
}

QStringList CategoricalCompleter::splitPath(const QString &path) const
{
//    if (sep.isNull()) {
//        return QCompleter::splitPath(path);
//    }

    return path.split(" ");
}

QString CategoricalCompleter::pathFromIndex(const QModelIndex &index) const
 {

     // navigate up and accumulate data
     QStringList dataList;
     for (QModelIndex i = index; i.isValid(); i = i.parent()) {
         dataList.prepend(model()->data(i, completionRole()).toString());
     }

     return dataList.join(" ");
 }

void CategoricalCompleter::updateCurrentSuggestions()
{
    QLineEdit*le=dynamic_cast<QLineEdit*>(widget());
    if(le) {
        QString search=le->text();
        QString newString=le->text();
        QString suffix=search;
        search.truncate(le->cursorPosition());
        suffix.remove(0,le->cursorPosition()+1);
        newString=search;
        search.remove(_completed);
        if(search.contains(" ")) {
            search.remove(0,search.lastIndexOf(" ")+1);
        }
//        qDebug()<<"S:"<<search;

        for(int i=_data.size()-1;i>=0;i--) {
            if((search==_data[i].prefix())) {
//                qDebug()<<"!"<<completionPrefix()<<"##"<<newString<<"##"<<suffix<<search;
                setCompletionPrefix(newString);
                if(popup()->isHidden()) {
//                    le->setText(newString);
                    setModel(new QStringListModel(join(_data[i],newString)));
                    complete();
                    _tableView->setData(&_data[i],newString);
                    _currentSubset=&_data[i];
                }
                break;
            }
        }
    }
    if(popup()->isHidden()) {
        complete();
    }
}

CategoricalCompleter::~CategoricalCompleter()
{
    //_tableView is child
}

QStringList CategoricalCompleter::join(CompletionCase& l,QString prefix)
{
    QStringList ret;
    for(int i=0;i<l.size();i++) {
        ret<<l[i];
    }
    if(prefix.size()) {
        for(int i=0;i<ret.size();i++) {
            ret[i].prepend(prefix);
        }
    }
    return ret;
}

// CCLineEdit
void CCLineEdit::keyPressEvent(QKeyEvent*ev)
{
//    _cc->_tableView->keyPressEvent(ev);

    QLineEdit::keyPressEvent(ev);
    setText(text()+"");
//    show();
}

void CCLineEdit::init()
{
}

// CCTableModel

int CCTableModel::rowCount(const QModelIndex &parent=QModelIndex()) const
{
    Q_UNUSED(parent);

    int max=0;
    for(int i=0;i<_visibleData.size();i++) {
        max=qMax(max,_visibleData[i].size());
    }
    return max-1; // top row is title
}

int CCTableModel::columnCount(const QModelIndex &parent=QModelIndex()) const
{
    Q_UNUSED(parent);
    return _visibleData.size();
}

QVariant CCTableModel::data(const QModelIndex &index, int role) const
{
    if(role!=Qt::DisplayRole) return QVariant();  // Return unvalid QVariant
    Q_ASSERT(index.column()<columnCount());
    if (index.row()+1>=_visibleData[index.column()].size()) return QVariant("");  // +1 because top row is title
    return _visibleData[index.column()][index.row()+1]; // +1 because top row is title
}

Qt::ItemFlags CCTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant CCTableModel::headerData ( int section, Qt::Orientation orientation, int role ) const
{
    Q_UNUSED(orientation);
    if(role!=Qt::DisplayRole) return QVariant();
    else return _visibleData[section][0];
}

// CCTableView

CCTableView::CCTableView(CompletionCase* data) : _data(data), origModel(0), completer(0)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setMinimumHeight(150);
//    setMinimumWidth(300);
    verticalHeader()->hide();
}

void CCTableView::updateSuggestions()
{
    if(!model()) {
        return;
    }

    if(!origModel) origModel=model();
    else delete model();

//    completer->updateCurrentSuggestions();

    QList<QStringList> items;
    for(int i=0;i<_data->size();i++) {
        items.push_back(QStringList());
        items[i].push_back((*_data)[i].title());
    }
    bool ok=0;
    qDebug()<<"### COUNT:"<<completer->completionCount();
    for(int i=0;i<completer->completionCount();i++) {
//        QString item=origModel->data(origModel->index(i,0)).toString();
        completer->setCurrentRow(i);
        QString item=completer->currentCompletion();
        item.remove(_prefix);
        item.remove(0,item.lastIndexOf(" ")+1);
        int x=-1;
        for(int j=0;j<_data->size();j++) {
//            qDebug()<<(*_data)[j];
            switch((*_data)[j].indexOf(item)) {
            case -1:
                break;
            default:
                qDebug()<<"ADD";
                x=j;
                break;
            }
            if(x==j) break;
        }
        if(x!=-1) {
            ok=1;
            items[x]<<_data->prefix()+item;
        }
    }
    setModel(new CCTableModel(items));
    int minOK=-1;
    for(int i=0;i<_data->size();i++) {
        if(items[i].size()>1) {
            minOK=i;
            break;
        }
    }
    if(minOK!=-1) {
        setCurrentIndex(model()->index(0,minOK));
    }

    resizeColumnsToContents();
    show();
}

void CCTableView::setColumnHeaders(QStringList columnHeaders)
{
    for(int i=0;i<columnHeaders.size();i++) {
        model()->setHeaderData(i,Qt::Horizontal,columnHeaders[i]);
    }
}

void CCTableView::setCompleter(CategoricalCompleter* completer)
{
    this->completer=completer;
}

void CCTableView::setData(CompletionCase* data,QString prefix)
{
    _prefix=prefix;
    _data=data;
    origModel=0;
    updateSuggestions();
    updateSuggestions();
}

void CCTableView::keyPressEvent(QKeyEvent *event)
{
//        qDebug()<<event->key();
    QTableView::keyPressEvent(event);
}

void CCTableView::mousePressEvent(QMouseEvent *event)
{
    QTableView::mousePressEvent(event);
    QString x=prefix();
    x.chop(_data->prefix().size());
    completer->setCompletionPrefix(x+currentIndex().model()->data(currentIndex()).toString());
}

void CCTableView::showEvent(QShowEvent *)
{
    qDebug()<<"Showing!!!";
//    scrollToTop();
}

void CCTableView::hideEvent(QHideEvent *)
{
//    show();
    qDebug()<<"Hiding!!!";
    qDebug()<<"Now:"<<completer->completionCount();;
}
