#ifndef ISTRING_H
#define ISTRING_H

#include "imetatext.h"
#include <QColor>
#include <QString>
#include <QDebug>

/* Low level */
class IString
{
    friend class ISelection;
    friend class IDocument;
    QString s_string;

    // PER CHARACTER FIELDS:
    IMetaText<bool> s_bold;
    IMetaText<bool> s_italic;
    IMetaText<bool> s_underlined;
    IMetaText<bool> s_strike;
    IMetaText<bool> s_subscript;
    IMetaText<bool> s_superscript;
    IMetaText<QColor> s_background;
    IMetaText<QColor> s_foreground;
    IMetaText<QString> s_fonttype;
    IMetaText<int> s_fontsize;

public:
    enum Alignment { Left=0, Center=1, Right=2, Justified=3 };
protected:
    // PER LINE FIELDS:
    IMetaText<Alignment> s_align;

public:
    IString() {
        s_bold.set(0,1,0);
        s_italic.set(0,1,0);
        s_underlined.set(0,1,0);
        s_strike.set(0,1,0);
        s_subscript.set(0,1,0);
        s_superscript.set(0,1,0);
        s_background.set(0,1,"white");
        s_foreground.set(0,1,"black");
        s_fonttype.set(0,1,"DejaVu Sans");
        s_fontsize.set(0,1,11);
        s_align.set(0,1,Left);
    }

    void insert(const int& i,const QString& str) {
        int newNewlines=str.count('\n');

        s_string.insert(i,str);
        if(newNewlines) {
            QString tmp=s_string;
            tmp.truncate(i);
            int prevNewlines=tmp.count('\n');
            s_align.extend(prevNewlines+1,newNewlines);
        }
        s_bold.extend(i,str.size());
        s_italic.extend(i,str.size());
        s_underlined.extend(i,str.size());
        s_strike.extend(i,str.size());
        s_subscript.extend(i,str.size());
        s_superscript.extend(i,str.size());
        s_background.extend(i,str.size());
        s_foreground.extend(i,str.size());
        s_fonttype.extend(i,str.size());
        s_fontsize.extend(i,str.size());
    }

    void remove(const int& i,const int& len) {
        Q_ASSERT(len>0);
        QString substring=s_string;
        substring.remove(0,i);
        substring.truncate(len);
        int delNewlines=substring.count('\n');
        if(delNewlines) {
            QString tmp=s_string;
            tmp.truncate(i);
            int prevNewlines=tmp.count('\n');
            s_align.contract(prevNewlines+1,delNewlines-1);
        }
        s_string.remove(i,len);
        s_bold.contract(i,len);
        s_italic.contract(i,len);
        s_underlined.contract(i,len);
        s_strike.contract(i,len);
        s_subscript.contract(i,len);
        s_superscript.contract(i,len);
        s_background.contract(i,len);
        s_foreground.contract(i,len);
        s_fonttype.contract(i,len);
        s_fontsize.contract(i,len);
    }
    int size() const { return s_string.size(); }
};

#endif // ISTRING_H
