#ifndef IACTION_H
#define IACTION_H

#include <vector>

class IAction {
    static std::vector<IAction*> s_undo;
    static std::vector<IAction*> s_redo;

public:
    static inline bool canUndo() { return s_undo.size(); }
    static inline bool canRedo() { return s_redo.size(); }
    static void globalUndo() { if(s_undo.size()) { s_undo.back()->undo(); s_redo.push_back(s_undo.back()); s_undo.pop_back(); } }
    static void globalRedo() { if(s_redo.size()) { s_redo.back()->redo(); s_undo.push_back(s_redo.back()); s_redo.pop_back(); } }

    IAction() { s_undo.push_back(this); while(s_redo.size()) { delete s_redo.back(); s_redo.pop_back(); } }

    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual const char* description() = 0;
};

#ifndef ICALL_MEMBER_FN
#define ICALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
#endif

// Let T represent the classtype
// Let U represent the member function type to redo the action and V represent the respective member function argument type
// Let W represent the member function type to undo the action and V represnet the respective member function argument type

template < class T, class U, class V, class W, class X > class ISimpleAction : public IAction {
    T* s_class;
    U s_redoFunc;
    V s_redoArg;
    W s_undoFunc;
    X s_undoArg;
    const char* s_desc;
public:
    ISimpleAction(T* t,U u,V v,W w,X x,const char* desc) : s_class(t), s_redoFunc(u), s_redoArg(v), s_undoFunc(w), s_undoArg(x), s_desc(desc) { redo(); }
    inline void undo() {
        ICALL_MEMBER_FN(*s_class,s_undoFunc)(s_undoArg);
    }
    inline void redo() {
        ICALL_MEMBER_FN(*s_class,s_redoFunc)(s_redoArg);
    }
    const char* description() { return s_desc; }
};


#endif // IACTION_H
