/* a weekend project */

#include "iaction.h"

QList<IAction*> IAction::s_undoStack;
QList<IAction*> IAction::s_redoStack;

IAction::IAction()
{
    if(s_redoStack.size())
    {
        s_redoStack.clear();
    }
    s_undoStack.push_back(this);
}

void IAction::globalRedo()
{
    if(s_redoStack.size())
    {
        s_redoStack.back()->redo();
        s_undoStack.push_back(s_redoStack.takeLast());
    }
}

void IAction::globalUndo()
{
    if(s_undoStack.size())
    {
        s_undoStack.back()->undo();
        s_redoStack.push_back(s_undoStack.takeLast());
    }
}
