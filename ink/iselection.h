#ifndef ISELECTION_H
#define ISELECTION_H

#include "iaction.h"
#include "imetatext.h"
#include "istring.h"

#include <QString>
#include <QObject>
#include <QColor>
#include <QDebug>
#include <QMap>
#include <QTest>

class QClipboard;

bool operator<(QColor a,QColor b);

class ISelection : public QObject
{
    friend class IDocument;
    Q_OBJECT
    QClipboard* s_clipboard;
    IString* s_document;
    int s_begin,s_end;
    int s_anchor;
    int s_firstLine, s_lastLine;

    int s_boldOnType;
    int s_italicOnType;
    int s_underlinedOnType;
    int s_strikeOnType;
    int s_subscriptOnType;
    int s_superscriptOnType;
    QColor s_bgOnType;
    QColor s_fgOnType;
    QString s_fontTypeOnType;
    int s_fontSizeOnType;

public:
    ISelection(QObject* parent,IString* document);

    bool bold() const { if(s_boldOnType!=-1) return s_boldOnType; else return s_document->s_bold.mode(s_begin,s_end); }
    bool italic() const { if(s_italicOnType!=-1) return s_italicOnType; else return s_document->s_italic.mode(s_begin,s_end); }
    bool underlined() const { if(s_underlinedOnType!=-1) return s_underlinedOnType; else return s_document->s_underlined.mode(s_begin,s_end); }
    bool strike() const { if(s_strikeOnType!=-1) return s_strikeOnType; else return s_document->s_strike.mode(s_begin,s_end); }
    bool subscript() const { if(s_subscriptOnType!=-1) return s_subscriptOnType; else return s_document->s_subscript.mode(s_begin,s_end); }
    bool superscript() const { if(s_superscriptOnType!=-1) return s_superscriptOnType; else return s_document->s_superscript.mode(s_begin,s_end); }
    int fontsize() const { if(s_fontSizeOnType!=-1) return s_fontSizeOnType; else return s_document->s_fontsize.mode(s_begin,s_end); }
    QColor background() const { if(s_bgOnType.isValid()) return s_bgOnType; else return s_document->s_background.mode(s_begin,s_end); }
    QColor foreground() const { if(s_fgOnType.isValid()) return s_fgOnType; else return s_document->s_foreground.mode(s_begin,s_end); }
    QString fonttype() const { if(s_fontTypeOnType!="NO-CHANGE-ON-TYPE") return s_fontTypeOnType; else return s_document->s_fonttype.mode(s_begin,s_end); }

public slots:
    void cut() { new Cut(this); }
    void copy() { new Copy(this); }
    void paste() { new Paste(this); }

    void setBold(const bool& bold) { new Bold(this,bold); }
    void setItalic(const bool& italic) { new Italic(this,italic); }
    void setUnderlined(const bool& underlined) { new Underlined(this,underlined); }
    void setStrike(const bool& strike) { new Strike(this,strike); }
    void setSubscript(const bool& subscript) { new Subscript(this,subscript); }
    void setSuperscript(const bool& superscript) { new Superscript(this,superscript); }
    void setBackground(const QColor& background) { new Background(this,background); }
    void setForeground(const QColor& foreground) { new Foreground(this,foreground); }
    void setFonttype(const QString& fonttype) { new Fonttype(this,fonttype); }
    void setFontsize(const int& fontsize) { new Fontsize(this,fontsize); }

    void setAlignLeft(bool b) { if(b) new Align(this,IString::Left); }
    void setAlignCenter(bool b) { if(b) new Align(this,IString::Center); }
    void setAlignJustify(bool b) { if(b) new Align(this,IString::Justified); }
    void setAlignRight(bool b) { if(b) new Align(this,IString::Right); }

    void updateState();
    void backspace() { if(s_begin) new RemoveText(this); }
    void setText(const QString&str) { /*if(dynamic_cast<ChangeText*>(IAction::lastAction())&&s_begin==s_end) dynamic_cast<ChangeText*>(IAction::lastAction())->cont(str); else */new ChangeText(this,str); }
    void goLeft(bool sel) {if(s_begin) new Go(this,-1,sel);}
    void goRight(bool sel) {if(s_end!=s_document->s_string.size()) new Go(this,1,sel);}
    void setPos(const int& pos,bool sel=0) { new Go(this,pos-s_begin,sel); }

signals:
    void canCutChanged(bool);
    void canPasteChanged(bool);

    void boldChanged(bool);
    void italicChanged(bool);
    void underlinedChanged(bool);
    void strikeChanged(bool);
    void subscriptChanged(bool);
    void superscriptChanged(bool);
    void fontsizeChanged(int);
    void bgChanged(QColor);
    void fgChanged(QColor);
    void fonttypeChanged(QString);
    void textChanged();
protected:
    QString text() const {if(s_begin==s_end) return ""; QString a=s_document->s_string;a.remove(0,s_begin);a.truncate(s_end-s_begin);return a;}


    /////////////////// ACTIONS ///////////////////


    class Cut : public IAction {
        ISelection* s_parent;
        QString s_cut;
        QString s_oldClipboard;
    public:
        Cut(ISelection* parent);
        void redo();
        void undo();
    };

    class Copy : public IAction {
        ISelection* s_parent;
        QString s_copy;
        QString s_oldClipboard;
    public:
        Copy(ISelection* parent);
        void redo();
        void undo();
    };

    class Paste : public IAction {
        QString s_paste;
        QString s_oldText;
        ISelection* s_parent;
    public:
        Paste(ISelection* parent);
        void redo();
        void undo();
    };

    class Bold : public IAction {
        ISelection* s_parent;
        bool s_bold;
        IMetaText<bool> s_oldBold;

    public:
        Bold(ISelection* parent, bool bold);
        void redo();
        void undo();
    };

    class Italic : public IAction {
        ISelection* s_parent;
        bool s_italic;
        IMetaText<bool> s_oldItalic;

    public:
        Italic(ISelection* parent, bool italic);
        void redo();
        void undo();
    };

    class Underlined : public IAction {
        ISelection* s_parent;
        bool s_underlined;
        IMetaText<bool> s_oldUnderlined;

    public:
        Underlined(ISelection* parent, bool underlined);
        void redo();
        void undo();
    };

    class Strike : public IAction {
        ISelection* s_parent;
        bool s_strike;
        IMetaText<bool> s_oldStrike;

    public:
        Strike(ISelection* parent, bool strike);
        void redo();
        void undo();
    };

    class Subscript : public IAction {
        ISelection* s_parent;
        bool s_subscript;
        IMetaText<bool> s_oldSubscript;

    public:
        Subscript(ISelection* parent, bool subscript);
        void redo();
        void undo();
    };

    class Superscript : public IAction {
        ISelection* s_parent;
        bool s_superscript;
        IMetaText<bool> s_oldSuperscript;

    public:
        Superscript(ISelection* parent, bool superscript);
        void redo();
        void undo();
    };

    class Background : public IAction {
        ISelection* s_parent;
        QColor s_background;
        IMetaText<QColor> s_oldBackground;

    public:
        Background(ISelection* parent, QColor background);
        void redo();
        void undo();
    };

    class Foreground : public IAction {
        ISelection* s_parent;
        QColor s_foreground;
        IMetaText<QColor> s_oldForeground;

    public:
        Foreground(ISelection* parent, QColor foreground);
        void redo();
        void undo();
    };

    class Fonttype : public IAction {
        ISelection* s_parent;
        QString s_fonttype;
        IMetaText<QString> s_oldFonttype;

    public:
        Fonttype(ISelection* parent, QString fonttype);
        void redo();
        void undo();
    };

    class Fontsize : public IAction {
        ISelection* s_parent;
        int s_fontsize;
        IMetaText<int> s_oldFontsize;

    public:
        Fontsize(ISelection* parent, int fontsize);
        void redo();
        void undo();
    };

    class ChangeText : public IAction {
        ISelection* s_parent;
        QString s_txt;
        QString s_oldTxt;
        int s_begin, s_end;
        int bk_first, bk_last;

    public:
        ChangeText(ISelection* parent, QString text);
        void redo();
        void undo();
        void cont(QString txt);
    };

    class RemoveText : public IAction {
        ISelection* s_parent;
        QString s_oldTxt;
        int s_begin, s_end;
        int bk_first, bk_last;

    public:
        RemoveText(ISelection* parent);
        void redo();
        void undo();
    };

    class Go : public IAction {
        ISelection* s_parent;
        int s_pos;
        bool s_sel;
        int s_lines;

    public:
        Go(ISelection* parent, int pos,bool sel=0) : s_parent(parent), s_pos(pos),s_sel(sel)
        {
            QString substring=s_parent->s_document->s_string;

            if(s_pos>0) {
                substring.remove(0,s_parent->s_begin);
                substring.truncate(s_pos);
                s_lines=substring.count('\n');
            } else {
                substring.remove(0,s_parent->s_begin+s_pos);
                substring.truncate(-s_pos);
                s_lines=-substring.count('\n');
            }
            redo();
        }
        void redo() {
//            s_parent->s_firstLine+=s_lines;
//            s_parent->s_lastLine+=s_lines;
            if(s_sel) {
                if(s_pos>0) {
                    s_parent->s_end+=s_pos;
                } else if(s_pos<0){
                    s_parent->s_begin+=s_pos;
                }
            } else {
                s_parent->s_begin+=s_pos;
                s_parent->s_end=s_parent->s_begin;
            }

            bool begunFirst=0;
            s_parent->s_firstLine=0;
            s_parent->s_lastLine=0;
            for(int i=0;i<s_parent->s_document->s_string.size()&&i<s_parent->s_end;i++) {
                if(s_parent->s_document->s_string[i]=='\n') {
                    if(i>=s_parent->s_begin) begunFirst=1;
                    if(!begunFirst) {
                        s_parent->s_firstLine++;
                    }
                    s_parent->s_lastLine++;
                }
            }

            s_parent->updateState();
        }
        void undo() {
            s_parent->s_firstLine-=s_lines;
            s_parent->s_lastLine-=s_lines;
            s_parent->s_begin-=s_pos;
            s_parent->s_end-=s_pos;
            if(s_parent->s_begin<0) s_parent->s_begin=0;
            s_parent->s_end=qMax(s_parent->s_begin,s_parent->s_end);
            s_parent->updateState();
        }
    };

    class Align : public IAction {
        ISelection* s_parent;
        IString::Alignment s_align;
        IMetaText<IString::Alignment> s_oldAlign;

    public:
        Align(ISelection* parent, IString::Alignment align);
        void redo();
        void undo();
    };

protected:

};

#endif // ISELECTION_H
