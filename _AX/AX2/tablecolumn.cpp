#include "tablecolumn.h"
#include "ui_tablecolumn.h"
#include "cclineedit.h"
using namespace Kst;

TableColumn::TableColumn(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TableColumn)
{
    ui->setupUi(this);
    QList<CompletionCase> x;
    x.push_back(CompletionCase("["));
    x.back().push_back(Category("Vectors"));
    x.back().back().push_back("One]");
    x.back().back().push_back("Two]");
    x.back().back().push_back("Three]");
    x.back().push_back(Category("Scalars"));
    x.back().back().push_back("Four]");
    x.back().back().push_back("Five]");
    x.back().back().push_back("Six]");
    ui->lineEdit->init(x);
}

TableColumn::~TableColumn()
{
    delete ui;
}
