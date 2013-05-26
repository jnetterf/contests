#ifndef ACLINEEDIT_H
#define ACLINEEDIT_H

#include <QtGui/QLineEdit>
#include <QStringList>
#include <QTableWidget>
#include <QHeaderView>
#include <QCompleter>
#include <QDebug>
#include <QStringListModel>

class ACCompleter : public QCompleter
{
    Q_OBJECT;
    QAbstractItemModel* tmodel;
public:
    void setTModel(QAbstractItemModel* model)
    {
        tmodel=model;
    }
};

class ACTableModel : public QAbstractTableModel
{
    Q_OBJECT;
    QStringList d_data[2];
public:
    ACTableModel(QStringList listA,QStringList listB)
    {
        d_data[0]=listA;
        d_data[1]=listB;
        qDebug()<<d_data[0].size()<<","<<d_data[1].size();
    }

    int rowCount(const QModelIndex &parent) const
    {
        return qMax(d_data[0].size(),d_data[1].size());
    }
    int columnCount(const QModelIndex &parent) const
    {
        return 2;
    }
    QVariant data(const QModelIndex &index, int role) const
    {
        if(role!=Qt::DisplayRole)
            return QVariant();
        Q_ASSERT(index.column()<2);
        if (index.row()>=d_data[index.column()].size())
        {
            return QVariant(QString());
        }

        return d_data[index.column()][index.row()];
    }
    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        return Qt::ItemIsEnabled;
    }
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const
    {
        if(role!=Qt::DisplayRole) return QVariant();
        else return "Test";
    }
};

class ACTableView;

class ACLineEdit : public QLineEdit
{
    Q_OBJECT
    ACTableView* tableView;
    ACCompleter* completer;
public:
    ACLineEdit(QWidget *parent = 0);
    ~ACLineEdit();
};


class ACTableView : public QTableView
{
    Q_OBJECT
    QStringList groups[2];
    QAbstractItemModel* origModel;
    ACCompleter* completer;
public:
    ACTableView(QStringList group1, QStringList group2) : origModel(0), completer(0)
    {
        groups[0]=group1;
        groups[1]=group2;
        setMinimumHeight(150);
        setMinimumWidth(300);
        verticalHeader()->hide();
    }
public slots:
    void updateSuggestions()
    {
        if(!model())
        {
            return;
        }
        if(!origModel)
        {
            origModel=model();
        }
        else
        {
            delete model();
        }

        QStringList items[2];
        for(int i=0;i<origModel->rowCount();i++)
        {
            const QString& item=origModel->data(origModel->index(i,0)).toString();
            int x=-1;
            if(groups[0].contains(item)) x=0;
            else if(groups[1].contains(item)) x=1;
            if(x!=-1) items[x]<<origModel->data(origModel->index(i,0)).toString();
        }
        setModel(new ACTableModel(items[0],items[1]));

        if(completer)
        {
            completer->setTModel(model());
        }
    }

    void setColumnHeaders(QStringList columnHeaders)
    {
        for(int i=0;i<columnHeaders.size();i++)
        {
            qDebug()<<model()->metaObject()->className();
            model()->setHeaderData(i,Qt::Horizontal,columnHeaders[i]);
        }
    }
    QModelIndex indexAt(const QPoint &p) const
    {
        QModelIndex x=QTableView::indexAt(p);
        if(!model()||!origModel) return x;
        QString searchString=model()->data(x).toString();
        for(int i=0;i<origModel->rowCount();i++)
        {
            if(origModel->data(origModel->index(i,0)).toString()==searchString)
            {
                qDebug()<<origModel->data(origModel->index(i,0)).toString()<<"vs"<<searchString;
                return origModel->index(i,0);
            }
        }

    }
public slots:
    void setCompleter(ACCompleter* completer)
    {
        this->completer=completer;
    }
};


#endif // ACLINEEDIT_H
