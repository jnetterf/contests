/* a weekend project */

#ifndef RIBBON_H
#define RIBBON_H

#include <QTabWidget>
#include "idocument.h"

namespace Ui {
    class Ribbon;
}

class IRibbon : public QTabWidget
{
    Q_OBJECT

    IDocument* s_doc;

public:
    explicit IRibbon(QWidget *parent = 0);
    void init(IDocument* doc);
    ~IRibbon();

public slots:
    void undo() {
        IAction::globalUndo();
    }
    void selectColour();

private:
    Ui::Ribbon *ui;
};

#endif // RIBBON_H
