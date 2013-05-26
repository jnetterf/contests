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

#include "cclineedit.h"
#include "cclineedit_p.h"

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
#include <QHash>
#include <QMenu>

namespace Kst {

// CompletionCase
bool operator<(const CompletionCase&a,const CompletionCase&b)
{
    return a.prefix().size()<b.prefix().size();
}

// CategoricalCompleter
CategoricalCompleter::CategoricalCompleter(QLineEdit *lineEdit, QList<CompletionCase> data) : QCompleter(getDefault(data)),
    _data(data), _tableView(new CCTableView(&_data[0])), _currentSubset(&data[0])
{
    setPopup(_tableView);
    lineEdit->setCompleter(this);
    _tableView->setCompleter(this);
    _tableView->updateSuggestions();
    setCompletionMode(PopupCompletion);
    setCaseSensitivity(Qt::CaseInsensitive);
    setWrapAround(false);
    qSort(_data.begin(),_data.end());
    connect(_tableView,SIGNAL(activateHint(QString)),this,SIGNAL(activated(QString)));
}

CategoricalCompleter::CategoricalCompleter(QTextEdit *textEdit, QList<CompletionCase> data) : QCompleter(getDefault(data)),
    _data(data), _tableView(new CCTableView(&_data[0])), _currentSubset(&data[0])
{
    setPopup(_tableView);
    _tableView->setCompleter(this);
    _tableView->updateSuggestions();
    setCompletionMode(PopupCompletion);
    setCaseSensitivity(Qt::CaseInsensitive);
    setWrapAround(false);
    qSort(_data.begin(),_data.end());
    connect(_tableView,SIGNAL(activateHint(QString)),this,SIGNAL(activated(QString)));
}

bool CategoricalCompleter::eventFilter(QObject *o, QEvent *e)
{
    if(e->type()!=QEvent::KeyPress) {
        return QCompleter::eventFilter(o,e);
    } else {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        int key=ke->key();
        int cc=_tableView->currentIndex().column();
        bool cantMoveRight=(cc==_tableView->model()->columnCount()-1);
        bool cantMoveLeft=!cc;
        if(!cantMoveLeft) {
            bool ok=1;
            for(int i=0;i<cc;i++) {
                if(_tableView->model()->data(_tableView->model()->index(_tableView->currentIndex().row(),i)).toString()!="") {
                    ok=0;
                    break;
                }
            }
            cantMoveLeft=ok;
        }
        if(!cantMoveRight) {
            bool ok=1;
            for(int i=cc+1;i<_tableView->model()->columnCount();i++) {
                if(_tableView->model()->data(_tableView->model()->index(_tableView->currentIndex().row(),i)).toString()!="") {
                    ok=0;
                    break;
                }
            }
            cantMoveRight=ok;

        }
        if((key!=Qt::Key_Left||!cantMoveLeft)&&(key!=Qt::Key_Right||!cantMoveRight)) {
            if(_tableView->isVisible()) {
                _tableView->keyPressEvent(ke);
            }
        }

        if(_tableView->isHidden()||((key!=Qt::Key_Enter)&&(key!=Qt::Key_Return)/*&&(key!=Qt::Key_Space)*/&&(key!=Qt::Key_Up)&&(key!=Qt::Key_Down&&key!=Qt::Key_PageDown&&key!=Qt::Key_PageUp))) {
            if(_tableView->isHidden()||(((key==Qt::Key_Left&&cantMoveLeft)||(key==Qt::Key_Right&&cantMoveRight))||(key!=Qt::Key_Left&&key!=Qt::Key_Right))) {
                if(_tableView->isHidden()||(!(cantMoveRight&&key==Qt::Key_Right&&_tableView->widgetCursorPosition()==_tableView->widgetText().size()))) {
                    if(_tableView->isHidden()||(!(cantMoveLeft&&key==Qt::Key_Left&&!_tableView->widgetCursorPosition()))) {
                        if(key!=Qt::Key_Alt&&key!=Qt::Key_Shift) {
                            _tableView->_goingRight=key==Qt::Key_Right;
                            (static_cast<QObject *>(widget()))->event(ke);  //in QWidget, event(...) is protected
                        }
                    }
                }
            }
        }
        switch (key) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Tab:
            if(_tableView->isVisible()) {
                if(_tableView->currentIndex().row()!=-1&&_tableView->currentIndex().column()!=-1) {
                    setCompletionPrefix(_tableView->currentIndex().model()->data(_tableView->currentIndex()).toString());
                    emit activated(completionPrefix());
                    _tableView->hide();
                }
            }
            break;

        case Qt::Key_Backtab:
        case Qt::Key_Escape:
            _tableView->hide();
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

QStringList CategoricalCompleter::getDefault(QList<CompletionCase>& ccl)
{
    for(int i=0;i<ccl.size();i++) {
        if(ccl[i].prefix()=="") {
            return join(ccl[i]);
        }
    }
    //if none found:
    ccl.push_back(CompletionCase(""));
    return join(ccl.back());
}

// CCLineEdit and CCTextEdit
CCLineEdit::CCLineEdit(QWidget*p) : QLineEdit(p), _cc() { }
CCTextEdit::CCTextEdit(QWidget*p) : QTextEdit(p), _cc() { }

CCLineEdit::CCLineEdit(const QString &s, QWidget *p) : QLineEdit(s,p), _cc() { }
CCTextEdit::CCTextEdit(const QString &s, QWidget *p) : QTextEdit(s,p), _cc() { }

CCLineEdit::~CCLineEdit() { delete _cc; }
CCTextEdit::~CCTextEdit() { delete _cc; }

void CCLineEdit::insert(const QString &i,bool completion)
{
    QString x=text(),y=text();
    y.remove(0,cursorPosition());
    x.truncate(cursorPosition());

    if(completion) {
        bool caught=0;
        if(i.size()) {
            caught= i[i.size()-1]==']';     // this is a hard-coded exception to allow spaces in vector or scalar names. make less hacky
        }

        QChar search;
        if(caught) {
            search='[';
        } else {
            const QString& possiblePhraseEndings=" +-=$.\n:/*]()%^&|!<>";
            // also change in divide!!
            int maxIndex=-1;
            for(int j=0;j<possiblePhraseEndings.size();j++) {
                if(x.lastIndexOf(possiblePhraseEndings[j])>maxIndex) {
                    maxIndex=x.lastIndexOf(possiblePhraseEndings[j]);
                    search=possiblePhraseEndings[j];
                }
            }
        }

        if(x.lastIndexOf(search)!=-1) {
            x.remove(x.lastIndexOf(search)+(caught?0:1),999999);
        } else {
            x.remove(0,x.size());
        }
    }
    setText(x+i+y);
    setCursorPosition((x+i).size());
}

void CCTextEdit::insert(const QString &i)
{
    QString x=toPlainText(),y=toPlainText();
    y.remove(0,textCursor().position());
    x.truncate(textCursor().position());

    bool caught=0;
    if(i.size()) {
        caught = i[i.size()-1]==']';     // this is a hard-coded exception to allow spaces in vector or scalar names. make less hacky
    }

    QChar search;
    if(caught) {
        search='[';
    } else {
        const QString& possiblePhraseEndings=" +-=$.\n:/*]()%^&|!<>";
        // also change in divide!!
        int maxIndex=-1;
        for(int j=0;j<possiblePhraseEndings.size();j++) {
            if(x.lastIndexOf(possiblePhraseEndings[j])>maxIndex) {
                maxIndex=x.lastIndexOf(possiblePhraseEndings[j]);
                search=possiblePhraseEndings[j];
            }
        }
    }

    if(x.lastIndexOf(search)!=-1) {
        x.remove(x.lastIndexOf(search)+(caught?0:1),999999);
    }
    setText(x+i+y);
    QTextCursor tc=textCursor();
    tc.setPosition((x+i).size());
    setTextCursor(tc);
}

void CCLineEdit::divide(QString x)
{
    x=(x=="\0")?text():x;
    x.truncate(cursorPosition());

    // this is a hard-coded exception to allow spaces in vector or scalar names. make less hacky {

    bool caught = (x.indexOf("[")!=-1)&&(x.indexOf("]",x.lastIndexOf("["))==-1);
    if(caught) {
        caught=((x.lastIndexOf("\\[")==-1)||(x.lastIndexOf("\\[")+1!=x.lastIndexOf("[")));
    }

    //}

    QChar search;
    if(caught) {
        search='[';
    } else {
        const QString& possiblePhraseEndings=" +-=$.\n:/*]()%^&|!<>";
        // also change in insert!!

        int maxIndex=-2;
        for(int i=0;i<possiblePhraseEndings.size();i++) {
            if(x.lastIndexOf(possiblePhraseEndings[i])>maxIndex) {
                maxIndex=x.lastIndexOf(possiblePhraseEndings[i]);
                search=possiblePhraseEndings[i];
            }
        }
    }

    if(x.lastIndexOf(search)) {
        x.remove(0,x.lastIndexOf(search)+(caught?0:1));
    }

    emit currentPrefixChanged(x);
}

void CCTextEdit::divide(QString x)
{
    x=(x=="\0")?toPlainText():x;
    x.truncate(textCursor().position());

    // this is a hard-coded exception to allow spaces in vector or scalar names. make less hacky {

    bool caught = (x.indexOf("[")!=-1)&&(x.indexOf("]",x.lastIndexOf("["))==-1);
    if(caught) {
        caught=((x.lastIndexOf("\\[")==-1)||(x.lastIndexOf("\\[")+1!=x.lastIndexOf("[")));
    }

    //}

    QChar search;
    if(caught) {
        search='[';
    } else {
        const QString& possiblePhraseEndings=" +-=$.\n:/*]()%^&|!<>";
        // also change in insert!!

        int maxIndex=-2;
        for(int i=0;i<possiblePhraseEndings.size();i++) {
            if(x.lastIndexOf(possiblePhraseEndings[i])>maxIndex) {
                maxIndex=x.lastIndexOf(possiblePhraseEndings[i]);
                search=possiblePhraseEndings[i];
            }
        }
    }

    if(x.lastIndexOf(search)) {
        x.remove(0,x.lastIndexOf(search)+(caught?0:1));
    }

    emit currentPrefixChanged(x);
}

void CCLineEdit::keyPressEvent(QKeyEvent*ev)
{
    if(!_cc) {
        QLineEdit::keyPressEvent(ev);
        return;
    }
    _cc->_tableView->keyPressEvent(ev);
    QLineEdit::keyPressEvent(ev);
    _cc->_tableView->updateSuggestions();
}

void CCTextEdit::keyPressEvent(QKeyEvent*ev)
{
    if(!_cc) {
        QTextEdit::keyPressEvent(ev);
        return;
    }
    _cc->_tableView->keyPressEvent(ev);
    QTextEdit::keyPressEvent(ev);
    _cc->_tableView->updateSuggestions();
}

void CCLineEdit::init(QList<CompletionCase> data)
{
    delete _cc;

    _cc=new CategoricalCompleter(this,data);
    setCompleter(0);
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(divide(QString)));
    connect(this,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(divide()));

    connect(this,SIGNAL(currentPrefixChanged(QString)),_cc,SLOT(setCompletionPrefix(QString)));
    connect(_cc,SIGNAL(activated(QString)),this,SLOT(insert(QString)));
    _cc->_tableView->setLineEdit(this);
    _cc->setWidget(this);
}

void CCTextEdit::init(QList<CompletionCase> data)
{
    delete _cc;

    _cc=new CategoricalCompleter(this,data);
    connect(this,SIGNAL(textChanged()),this,SLOT(divide()));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(divide()));

    connect(this,SIGNAL(currentPrefixChanged(QString)),_cc,SLOT(setCompletionPrefix(QString)));
    connect(_cc,SIGNAL(activated(QString)),this,SLOT(insert(QString)));
    _cc->_tableView->setTextEdit(this);
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
    if(index.column()==-1) {
        return QVariant("");
    }
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
CCTableView::CCTableView(CompletionCase* data) : _data(data), origModel(0), completer(0), _le(0), _te(0), _goingRight(0)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setMinimumHeight(150);
    //    setMinimumWidth(300);
    verticalHeader()->hide();
}

void CCTableView::updateSuggestions()
{
    if(!model()||(!_le&&!_te)) {
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
    if(_le) {
        x.truncate(_le->cursorPosition());
    } else if (_te) {
        x.truncate(_te->textCursor().position());
    }

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
    int maxOK=-1;
    for(int i=0;i<_data->size();i++) {
        if(items[i].size()>1) {
            minOK=(minOK==-1)?i:minOK;
            maxOK=i;
        }
    }
    if(minOK!=-1) {
        setCurrentIndex(model()->index(0,_goingRight?maxOK:minOK));
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
    QPoint pos = event->pos();
    QModelIndex idx = indexAt(pos);
    setCurrentIndex(idx);
    if(currentIndex().row()!=-1&&currentIndex().column()!=-1)
    {
        completer->setCompletionPrefix(currentIndex().model()->data(currentIndex()).toString());
        emit activateHint(completer->completionPrefix());
        if(_le) {
            _le->insert(completer->completionPrefix());
        } else {
            _te->insert(completer->completionPrefix());
        }
        hide();
    }
}

void CCTableView::showEvent(QShowEvent *)
{
    //    resizeColumnsToContents();
    int bestWidth=qMax(width(),(int)((horizontalHeader()->length()+verticalScrollBar()->width())*1.05));
    horizontalHeader()->setStretchLastSection(1);
    setMinimumWidth(bestWidth);
    setMaximumWidth(bestWidth);
}

}
