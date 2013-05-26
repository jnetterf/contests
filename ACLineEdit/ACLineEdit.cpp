#include "ACLineEdit.h"
#include <QCompleter>
#include <QAbstractItemView>
#include <QStringListModel>

ACLineEdit::ACLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    QStringList listA,listB;
    for(int i=0;i<1500;i++)
    {
        listA<<QString::number(i);
        listB<<QString::number(i+1500);
    }
    QStringList fullList;
    fullList<<listA<<listB;

//    completer->setModel(new ACModel);
    QStringList headers;
    headers<<"Scalers"<<"Vectors";
    completer = new ACCompleter;
    completer->setModel(new QStringListModel(fullList));
    completer->setPopup(tableView=new ACTableView(listA,listB));
//    completer->setPopup(tableView);
    tableView->setColumnHeaders(QStringList("Scaler"));
    completer->setTModel(tableView->model());
    setCompleter(completer);
    tableView->setCompleter(completer);
    connect(this,SIGNAL(textChanged(QString)),tableView,SLOT(updateSuggestions()));
}

ACLineEdit::~ACLineEdit()
{

}
