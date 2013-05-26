/* a weekend project */

#ifndef IACTION_H
#define IACTION_H

#include <QList>

class IAction
{
    static QList<IAction*> s_undoStack;
    static QList<IAction*> s_redoStack;
public:
    static IAction* lastAction() { if(s_undoStack.size()) return s_undoStack.back(); else return 0; }
    static void globalUndo();
    static void globalRedo();

    IAction();
    virtual void undo()=0;
    virtual void redo()=0;
};

#endif // IACTION_H
