/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2011 Joshua Netterfield                               *
 *                   joshua.netterfield@gmail.com                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "CC.h"
#include "CC_p.h"
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
#include <QTableWidget>
#include <QHeaderView>
#include <QCompleter>


// CompletionCase
bool operator<(const CompletionCase&a,const CompletionCase&b)
{
    return a.prefix().size()<b.prefix().size();
}

// CategoricalCompleter
CategoricalCompleter::CategoricalCompleter(QLineEdit *lineEdit, QList<CompletionCase> *data) : QCompleter(join((*data)[0])),
    _tableView(new CCTableView(&(*data)[0])), _data(*data), _currentSubset(&(*data)[0])
{
    setPopup(_tableView);
    lineEdit->setCompleter(this);
    _tableView->setCompleter(this);
    _tableView->updateSuggestions();
    setCompletionMode(PopupCompletion);
    setCaseSensitivity(Qt::CaseInsensitive);
    setWrapAround(false);
    qSort(_data.begin(),_data.end());
}

bool CategoricalCompleter::eventFilter(QObject *o, QEvent *e)
{
    if(e->type()!=QEvent::KeyPress) {
        return QCompleter::eventFilter(o,e);
    } else {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        int key=ke->key();
        bool cantMoveRight=(_tableView->currentIndex().column()==_tableView->model()->columnCount()-1),cantMoveLeft=!(_tableView->currentIndex().column());
        if((key!=Qt::Key_Left||!cantMoveLeft)&&(key!=Qt::Key_Right||!cantMoveRight)) {
            _tableView->keyPressEvent(ke);
        }

        if(_tableView->isHidden()||((key!=Qt::Key_Enter)&&(key!=Qt::Key_Return)/*&&(key!=Qt::Key_Space)*/&&(key!=Qt::Key_Up)&&(key!=Qt::Key_Down&&key!=Qt::Key_PageDown&&key!=Qt::Key_PageUp))) {
            if(_tableView->isHidden()||(((key==Qt::Key_Left&&cantMoveLeft)||(key==Qt::Key_Right&&cantMoveRight))||(key!=Qt::Key_Left&&key!=Qt::Key_Right))) {
                if(_tableView->isHidden()||(!(cantMoveRight&&key==Qt::Key_Right&&_tableView->_le->cursorPosition()==_tableView->_le->text().size()))) {
                    if(_tableView->isHidden()||(!(cantMoveLeft&&key==Qt::Key_Left&&!_tableView->_le->cursorPosition()))) {
                        (static_cast<QObject *>(widget()))->event(ke);  //in children of QObject, event is protected
                    }
                }
            }
        }
        switch (key) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Tab:
            if(_tableView->currentIndex().row()!=-1&&_tableView->currentIndex().column()!=-1)
            {
                setCompletionPrefix(_tableView->currentIndex().model()->data(_tableView->currentIndex()).toString());
                emit activated(completionPrefix());
                _tableView->hide();
            }
            break;

        case Qt::Key_Backtab:
        case Qt::Key_Escape:
            _tableView->hide();
            break;

        case Qt::Key_Backspace:
        {
            QLineEdit*le=_tableView->_le;
            if(le) {
                if(_completed.size()>=le->text().size()) {
                    _completed=le->text();
                }
            }
        }
        break;
        default:
            break;
        }

        verifyPrefix();
    }
    return 1;
}

void CategoricalCompleter::verifyPrefix()
{
    QLineEdit*le=dynamic_cast<QLineEdit*>(widget());
    Q_ASSERT(le);

    QString search=completionPrefix();

    for(int i=_data.size()-1;i>=0;i--) {
        if(!_data[i].prefix().size()||!search.indexOf(_data[i].prefix())) {
            if(_currentSubset!=&_data[i]) {
                setModel(new QStringListModel(join(_data[i],_data[i].prefix())));
                _tableView->setData(&_data[i],_data[i].prefix());
                complete();
                _currentSubset=&_data[i];
            }
            break;
        }
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
CCLineEdit::CCLineEdit(QWidget*p) : QLineEdit(p), _cc() { }
CCLineEdit::CCLineEdit(const QString &s, QWidget *p) : QLineEdit(s,p), _cc() { }

void CCLineEdit::insert(const QString &i)
{
    QString x=text(),y=text();
    y.remove(0,cursorPosition());
    x.truncate(cursorPosition());
    if(x.lastIndexOf(" ")) {
        x.remove(x.lastIndexOf(" ")+1,999999);
    }
    setText(x+i+y);
    setCursorPosition((x+i).size());
}

void CCLineEdit::divide(QString x)
{
    x=(x=="\0")?text():x;
    x.truncate(cursorPosition());

    //make less hacky {

    bool caught = (x.indexOf("[")!=-1)&&(x.indexOf("]",x.lastIndexOf("["))==-1);
    if(caught) {
        caught=(x.lastIndexOf("\\[")!=-1&&x.lastIndexOf("\\[")+1!=x.lastIndexOf("["));
    }

    if(x.lastIndexOf(caught?"[":" ")) {
        x.remove(0,x.lastIndexOf(caught?"[":" ")+(caught?0:1));
    }

    //}
    emit newCurrentPrefix(x);
}

void CCLineEdit::keyPressEvent(QKeyEvent*ev)
{
    if(!_cc) {
        return;
    }
    _cc->_tableView->keyPressEvent(ev);
    QLineEdit::keyPressEvent(ev);
    _cc->_tableView->updateSuggestions();
}

void CCLineEdit::init(QList<CompletionCase> *data)
{
    _cc=new CategoricalCompleter(this,data);
    setCompleter(0);
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(divide(QString)));
    connect(this,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(divide()));

    connect(this,SIGNAL(newCurrentPrefix(QString)),_cc,SLOT(setCompletionPrefix(QString)));
    connect(_cc,SIGNAL(activated(QString)),this,SLOT(insert(QString)));
    _cc->_tableView->setLineEdit(this);
    _cc->setWidget(this);
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
CCTableView::CCTableView(CompletionCase* data) : _data(data), origModel(0), completer(0), _le(0)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setMinimumHeight(150);
    //    setMinimumWidth(300);
    verticalHeader()->hide();
}

void CCTableView::updateSuggestions()
{
    if(!model()||!_le) {
        return;
    }

    if(!origModel) origModel=model();
    else delete model();

    QList<QStringList> items;
    for(int i=0;i<_data->size();i++) {
        items.push_back(QStringList());
        items[i].push_back((*_data)[i].title());
    }
    QString x=completer->completionPrefix();
    x.truncate(_le->cursorPosition());

    for(int i=0;i<completer->completionCount();i++) {
        completer->setCurrentRow(i);
        QString item=completer->currentCompletion();
        item.remove(_prefix);
        int x=-1;
        for(int j=0;j<_data->size();j++) {
            switch((*_data)[j].indexOf(item)) {
            case -1:
                break;
            default:
                x=j;
                break;
            }
            if(x==j) break;
        }
        if(x!=-1) {
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
    completer->complete();
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
}

void CCTableView::keyPressEvent(QKeyEvent *event)
{
    QTableView::keyPressEvent(event);
}

void CCTableView::mousePressEvent(QMouseEvent *event)
{
    QTableView::mousePressEvent(event);
    completer->setCompletionPrefix(currentIndex().model()->data(currentIndex()).toString());    //
}

void CCTableView::showEvent(QShowEvent *)
{
}

