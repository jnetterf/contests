#include "iaction.h"

std::vector<IAction*> IAction::s_undo;
std::vector<IAction*> IAction::s_redo;
