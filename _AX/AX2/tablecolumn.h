#ifndef TABLECOLUMN_H
#define TABLECOLUMN_H

#include <QFrame>

namespace Ui {
    class TableColumn;
}

class TableColumn : public QFrame
{
    Q_OBJECT

public:
    explicit TableColumn(QWidget *parent = 0);
    ~TableColumn();

private:
    Ui::TableColumn *ui;
};

#endif // TABLECOLUMN_H
