#ifndef IPARAGRAPH_H
#define IPARAGRAPH_H

#include "icontainer.h"
#include "iaction.h"
#include <bitset>
#include <map>
#include <iostream>

class AspellConfig;
class AspellCanHaveError;
class AspellSpeller;

class IParagraph {
    friend int main();

    static AspellConfig* s_spellConfig;
    static AspellCanHaveError* s_canHaveError;
    static AspellSpeller* s_spellChecker;

//    IRopeContainer<wchar_t> s_str;
    IUniqueContainer<wchar_t> s_str;
    IContainer<std::bitset<13> > s_format;  // See FormatElement
    IContainer<float> s_size;
    IContainer<float> s_spacing;              // the actual spacing for the next line is determined by the mode of the line.
    IContainer<const wchar_t*> s_family;          // at every font family change, the font name ("Times New Roman\0"), otherwise null
    IContainer<const char*> s_fg;                 // at every foreground colour change, the font colour ("000000\0"), otherwise null
    IContainer<const char*> s_bg;                 // at every background colour change, the background colour ("FFFFFF\0"), otherwise null

    int s_indent;
    enum Align { Left=0, Center=1, Right=2, Justified=3 } s_alignment;
    enum ListMode { None=0, Numbering=1, Bullets=2 } s_listType;

    int s_number;   // for numbered list, or -1 for one more than previous, or if no previous, 1
    bool s_dirty;   // needs repainting
    bool s_locked;
    static std::bitset<13> s_defaultBitset;

    std::map<int, int> s_geometry;  // describes the geometry in the following way:
                                    // between two consecutive keys representing y-values, the paintable width is the value of the first key
                                    // if the width is zero, that represents text cannot be painted there, in px.

public:
    enum FormatElement {
        Bold=0,
        Italic=1,
        Underline_A=2,
        Underline_B=3,
        Underline_C=4,
        Underline_D=5,
        Underline_E=6,
        Underline_F=7,
        Underline_G=8,
        Underline_H=9,
        SuperOrSubScript=10,
        Subscript=11,    //N.B., if false and SuperOrSubScript is true, is superscript.
        SpellingCorrect=12
    };

public:
    IParagraph();
    virtual ~IParagraph();
    virtual void setGeometry(std::map<int, int>& geometry);

    //////////////////////////////////////////////
    // ACTIONS
    //////////////////////////////////////////////
    typedef void (IParagraph::*IParagraphConstWCharAction)(const wchar_t& t);
    typedef void (IParagraph::*IParagraphConstWCharPtrAction)(const wchar_t* t);
    typedef void (IParagraph::*IParagraphConstWCharPtrPtrAction)(const wchar_t** t);
    typedef void (IParagraph::*IParagraphConstCharPtrAction)(const char* t);
    typedef void (IParagraph::*IParagraphConstCharPtrPtrAction)(const char** t);
    typedef void (IParagraph::*IParagraphConstIntPtrAction)(const int* t);
    typedef bool (IParagraph::*IParagraphConstIntAction)(const int&);
    typedef void (IParagraph::*IParagraphConstBoolAction)(const wchar_t& t);
    typedef void (IParagraph::*IParagraphConstMapBoolIntAction)(const std::pair<bool,int>&);
    typedef void (IParagraph::*IParagraphConstMapIntIntAction)(const std::pair<int,int>&);
    typedef void (IParagraph::*IParagraphConstMapConstWCharPtrIntAction)(const std::pair<const wchar_t*,int>&);
    typedef void (IParagraph::*IParagraphConstMapConstCharPtrIntAction)(const std::pair<const char*,int>&);

    inline void insertChar_action(const wchar_t& t) {
        new ISimpleAction<IParagraph,IParagraphConstWCharAction,wchar_t,IParagraphConstIntAction,int>(this,&IParagraph::insertChar,t,&IParagraph::remove,1,"Insert Character");
    }
    inline void insertChars_action(const wchar_t* t) {
        int len=0;
        while(t[len]!='\0') ++len;
        new ISimpleAction<IParagraph,IParagraphConstWCharPtrAction,const wchar_t*,IParagraphConstIntAction,int>(this,&IParagraph::insertChars,t,&IParagraph::remove,len,"Insert Characters");
    }

    template<FormatElement T> inline void setFormatElement_action(const bool& value) {
        new ISimpleAction<IParagraph,IParagraphConstBoolAction,bool,IParagraphConstBoolAction,const bool&>(this,&IParagraph::setFormatElement<T>,value,
                                                                                                                  &IParagraph::setFormatElement<T>,getFormatElement<T>(),"Set Format");
    }
    template<FormatElement T> inline void setFormatElements_action(const bool& value,int count) {
        assert(count>0);
        char* backup=new char[count+1];
        backup[count]=2;

//        push();
//        for(int i=0;i<count;i++) {
//            backup[i]=getFormatElement<T>()?1:0;
//            next_unsafe();
//        }
//        pop();

        new ISimpleAction<IParagraph,IParagraphConstMapBoolIntAction,std::pair<bool,int>,IParagraphConstCharPtrAction,const char*>(this,&IParagraph::setFormatElements<T>,std::make_pair(value,count),
                                                                                                                                   &IParagraph::setFormatElements<T>,backup,"Set Format of Selection");
//        delete[]backup;
    }

    inline void setSize_action(const int& value) {
        new ISimpleAction<IParagraph,IParagraphConstIntAction,const int&,IParagraphConstIntAction,const int&>(this,&IParagraph::setSize,value,
                                                                                                                  &IParagraph::setSize,getSize(),"Set Font Size");
    }
    inline void setSizes_action(const int& value,int count) {
        assert(count>0);
        assert(value>0);
        int* backup = new int[count+1];
        backup[count]=-1;
        push();
        for(int i=0;i<count;i++) {
            backup[i]=getSize();
            next_unsafe();
        }
        pop();
//        for(int i=0;i<count;i++) prev();
        new ISimpleAction<IParagraph,IParagraphConstMapIntIntAction,std::pair<int,int>,IParagraphConstIntPtrAction,const int*>(this,&IParagraph::setSizes,std::make_pair(value,count),
                                                                                                                                   &IParagraph::setSizes,backup,"Set Font Size of Selection");
//        delete[]backup;
    }

    inline void setSpacing_action(const int& value) {
        new ISimpleAction<IParagraph,IParagraphConstIntAction,const int&,IParagraphConstIntAction,const int&>(this,&IParagraph::setSpacing,value,
                                                                                                                  &IParagraph::setSpacing,getSpacing(),"Set Spacing");
    }
    inline void setSpacings_action(const int& value,int count) {
        assert(count>0);
        assert(value>0);
        int* backup = new int[count+1];
        backup[count]=-1;
        for(int i=0;i<count;i++) {
            backup[i]=getSpacing();
            next_unsafe();
        }
        for(int i=0;i<count;i++) prev();
        new ISimpleAction<IParagraph,IParagraphConstMapIntIntAction,std::pair<int,int>,IParagraphConstIntPtrAction,const int*>(this,&IParagraph::setSpacings,std::make_pair(value,count),
                                                                                                                                   &IParagraph::setSpacings,backup,"Set Font Size of Selection");
//        delete[]backup;
    }
    inline void setFamily_action(const wchar_t* t) {
        new ISimpleAction<IParagraph,IParagraphConstWCharPtrAction,const wchar_t*,IParagraphConstWCharPtrAction,const wchar_t*>(this,&IParagraph::setFamily,t,
                                                                                                                  &IParagraph::setFamily,getFamily(),"Set Family");
    }
    inline void setFamilies_action(const wchar_t* value,int count) {
        assert(count>0);
        const wchar_t** backup = new const wchar_t*[count+1];
        backup[count]=0;
        for(int i=0;i<count;i++) {
            backup[i]=getFamily();
            next_unsafe();
        }
        for(int i=0;i<count;i++) prev();
        new ISimpleAction<IParagraph,IParagraphConstMapConstWCharPtrIntAction,std::pair<const wchar_t*,int>,IParagraphConstWCharPtrPtrAction,const wchar_t**>(this,&IParagraph::setFamilies,std::make_pair(value,count),
                                                                                                                                   &IParagraph::setFamilies,backup,"Set Font of Selection");
//        delete[]backup;
    }
    inline void setFg_action(const char* t) {
        new ISimpleAction<IParagraph,IParagraphConstCharPtrAction,const char*,IParagraphConstCharPtrAction,const char*>(this,&IParagraph::setFg,t,
                                                                                                                  &IParagraph::setFg,getFg(),"Set Text Colour");
    }
    inline void setFgs_action(const char* value,int count) {
        assert(count>0);
        const char** backup = new const char*[count+1];
        backup[count]=0;
        for(int i=0;i<count;i++) {
            backup[i]=getFg();
            next_unsafe();
        }
        for(int i=0;i<count;i++) prev();
        new ISimpleAction<IParagraph,IParagraphConstMapConstCharPtrIntAction,std::pair<const char*,int>,IParagraphConstCharPtrPtrAction,const char**>(this,&IParagraph::setFgs,std::make_pair(value,count),
                                                                                                                                   &IParagraph::setFgs,backup,"Set Text Colour of Selection");
//        delete[]backup;
    }
    inline void setBg_action(const char* t) {
        new ISimpleAction<IParagraph,IParagraphConstCharPtrAction,const char*,IParagraphConstCharPtrAction,const char*>(this,&IParagraph::setBg,t,
                                                                                                                  &IParagraph::setBg,getBg(),"Set Background Colour");
    }
    inline void setBgs_action(const char* value,int count) {
        assert(count>0);
        const char** backup = new const char*[count+1];
        backup[count]=0;
        for(int i=0;i<count;i++) {
            backup[i]=getBg();
            next_unsafe();
        }
        for(int i=0;i<count;i++) prev();
        new ISimpleAction<IParagraph,IParagraphConstMapConstCharPtrIntAction,std::pair<const char*,int>,IParagraphConstCharPtrPtrAction,const char**>(this,&IParagraph::setBgs,std::make_pair(value,count),
                                                                                                                                   &IParagraph::setBgs,backup,"Set Background Colour of Selection");
//        delete[]backup;
    }
    inline void prev_action(int amount=1) {
        if(amount<0) next_action(-amount);
        else new ISimpleAction<IParagraph,IParagraphConstIntAction,int,IParagraphConstIntAction,int>(this,&IParagraph::prev,amount,&IParagraph::next,amount,"Go Back");
    }

    inline void next_action(int amount=1) {
        if(amount<0) prev_action(-amount);
        else new ISimpleAction<IParagraph,IParagraphConstIntAction,int,IParagraphConstIntAction,int>(this,&IParagraph::next,amount,&IParagraph::prev,amount,"Go Forward");
    }

private:
    inline void insertChar(const wchar_t& t) {
        assert(!s_locked);
        s_dirty=1;
        s_str.insert(t);

        s_format.insert(s_format.prevValueExists()?s_format.prevValue():s_defaultBitset);
        s_size.insert(s_size.prevValueExists()?s_size.prevValue():11.5);
        s_spacing.insert(s_spacing.prevValueExists()?s_spacing.prevValue():0.);  //i.e., single
        s_family.insert(s_family.prevValueExists()?0:L"Test");
        s_fg.insert(s_fg.prevValueExists()?0:"00000");
        s_bg.insert(s_bg.prevValueExists()?0:"00000");
    }

    inline void insertChars(const wchar_t* t) {
        assert(!s_locked);
        while(*t) insertChar(*t++);
    }

    inline void setChar(const wchar_t& t) {
        assert(!s_locked);
        s_dirty=1;
        s_str.setValue(t);
    }
public:
//    const wchar_t& getChar() const { return s_str.value(); }
    wchar_t getChar() const { return s_str.value(); }

private:
    template<FormatElement T> inline void setFormatElement(const bool& value) {
        assert(!s_locked);
        s_dirty=1;
        std::bitset<13> l=s_format.value();
        l[T]=value;
        s_format.setValue(l);
    }
    template<FormatElement T> inline void setFormatElements(const char* values) {    //ending with 2
        assert(!s_locked);
        push();
        while(*values!=2) {
            setFormatElement<T>(*values++);
            next_unsafe();
        }
        pop();
    }
public: //tmp
    template<FormatElement T> inline void setFormatElements(const std::pair<bool,int>& pair) {  //{value,count}
        assert(!s_locked);
//        push();
        for(int i=0;i<pair.second;i++) {
            setFormatElement<T>(pair.first);
            next_unsafe();
        }
        for(int j=0;j<pair.second;j++) prev();
//        pop();
    }

public:
    template<FormatElement T> bool getFormatElement() const { return s_format.value()[T]; }

private:
    inline bool setSize(const int& size) {
        assert(!s_locked);
        s_dirty=1;
        s_size.setValue(size);
        return 1;
    }
    inline void setSizes(const int* sizes) {    //ending with -1
        assert(!s_locked);
        push();
        while(*sizes!=-1) {
            setSize(*sizes++);
            next_unsafe();
        }
        pop();
    }
    inline void setSizes(const std::pair<int,int>& pair) { //{sizes, count}
        push();
        for(int i=0;i<pair.second;i++) {
            setSize(pair.second);
            next_unsafe();
        }
        pop();
    }
public:
    int getSize() const { return s_size.value(); }

private:
    inline bool setSpacing(const int& spacing) {
        assert(!s_locked);
        s_dirty=1;
        s_spacing.setValue(spacing);
        return 1;
    }
    inline void setSpacings(const int* spacings) {  //ending with -1
        assert(!s_locked);
        push();
        while(*spacings!=-1) {
            setSpacing(*spacings++);
            next_unsafe();
        }
        pop();
    }
    inline void setSpacings(const std::pair<int,int>& pair) {   //{spacings,count}
        assert(!s_locked);
        push();
        for(int i=0;i<pair.second;i++) {
            setSpacing(pair.first);
            next_unsafe();
        }
        pop();
    }
public:
    int getSpacing() const { return s_spacing.value(); }

private:
    inline void setFamily(const wchar_t* family) {
        assert(!s_locked);
        s_dirty=1;
        s_family.setValue((s_family.prevValueExists()&&s_family.prevValue()!=family)?0:family);
    }
    inline void setFamilies(const wchar_t** families) { //ending with 0
        assert(!s_locked);
        push();
        while(*families) {
            setFamily(*families++);
            next_unsafe();
        }
        pop();
    }
    inline void setFamilies(const std::pair<const wchar_t*,int>& pair) {    //{families,count}
        assert(!s_locked);
        push();
        for(int i=0;i<pair.second;i++) {
            setFamily(pair.first);
            next_unsafe();
        }
        pop();
    }
public:
    const wchar_t* getFamily() const { return s_family.value(); }

private:
    inline void setFg(const char* fg) {
        assert(!s_locked);
        s_dirty=1;
        s_fg.setValue((s_fg.prevValueExists()&&s_fg.prevValue()!=fg)?0:fg);
    }
    inline void setFgs(const char** fgs) { //ending with 0
        assert(!s_locked);
        push();
        while(*fgs) {
            setFg(*fgs++);
            next_unsafe();
        }
        pop();
    }
    inline void setFgs(const std::pair<const char*,int>& pair) {    //{fgs,count}
        assert(!s_locked);
        push();
        for(int i=0;i<pair.second;i++) {
            setFg(pair.first);
            next_unsafe();
        }
        pop();
    }
public:
    const char* getFg() const { return s_fg.value(); }

private:
    inline void setBg(const char* bg) {
        assert(!s_locked);
        s_dirty=1;
        s_bg.setValue((s_bg.prevValueExists()&&s_bg.prevValue()!=bg)?0:bg);
    }
    inline void setBgs(const char** bgs) { //ending with 0
        assert(!s_locked);
        push();
        while(*bgs) {
            setBg(*bgs++);
            next_unsafe();
        }
        pop();
    }
    inline void setBgs(const std::pair<const char*,int>& pair) {    //{fgs,count}
        assert(!s_locked);
        push();
        for(int i=0;i<pair.second;i++) {
            setBg(pair.first);
            next_unsafe();
        }
        pop();
    }
public:
    const char* getBg() const { return s_bg.value(); }

private:
    inline bool remove(const int& count=1) {
        assert(!s_locked);
        s_dirty=1;
        int ret=0;
        for(int i=0;i<count;i++) {
            prev();
            s_str.remove();
            s_format.remove();
            s_size.remove();
            s_spacing.remove();
            s_family.remove();
            s_fg.remove();
            ret=s_bg.remove();

        }
        return ret;
    }

public:
    inline bool next(const int& i=1) {
        bool ret=0;
        for(int j=0;j<i;j++) {
            s_str.next_unsafe();
            s_format.next_unsafe();
            s_size.next_unsafe();
            s_spacing.next_unsafe();
            s_family.next_unsafe();
            s_fg.next_unsafe();
            ret=s_bg.next();
        }
        return ret;
    }

    inline void next_unsafe(const int& i=1) {
        for(int j=0;j<i;j++) {
            s_str.next_unsafe();
            s_format.next_unsafe();
            s_size.next_unsafe();
            s_spacing.next_unsafe();
            s_family.next_unsafe();
            s_fg.next_unsafe();
            s_bg.next_unsafe();
        }
    }

    inline bool prev(const int& i=1) {
        bool ret=0;
        for(int j=0;j<i;j++) {
            s_str.prev();
            s_format.prev();
            s_size.prev();
            s_spacing.prev();
            s_family.prev();
            s_fg.prev();
            ret=s_bg.prev();
        }
        return ret;
    }

    // backs up the iterator and allows the container to be read from the begining.
    inline void lock() {
        assert(!s_locked);
        s_locked=1;
        s_str.lock();
        s_format.lock();
        s_size.lock();
        s_spacing.lock();
        s_family.lock();
        s_fg.lock();
        s_bg.lock();
    }

    inline void unlock()
    {
        assert(s_locked);
        s_locked=0;
        s_str.unlock();
        s_format.unlock();
        s_size.unlock();
        s_spacing.unlock();
        s_family.unlock();
        s_fg.unlock();
        s_bg.unlock();
    }

    inline void push() {
        s_str.push();
        s_format.push();
        s_size.push();
        s_spacing.push();
        s_family.push();
        s_fg.push();
        s_bg.push();
    }

    inline void pop()
    {
        s_str.pop();
        s_format.pop();
        s_size.pop();
        s_spacing.pop();
        s_family.pop();
        s_fg.pop();
        s_bg.pop();
    }

    inline bool locked() { return s_locked; }

    void checkSpelling();
};

#endif // IPARAGRAPH_H
