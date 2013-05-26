#include "iselection.h"
#include <QApplication>
#include <QClipboard>

bool operator<(QColor a,QColor b) {
    return a.name()<b.name();
}

ISelection::ISelection(QObject *parent, IString *document) : QObject(parent), s_clipboard(QApplication::clipboard()), s_document(document), s_begin(0), s_end(0), s_anchor(-1), s_firstLine(0), s_lastLine(0),
    s_boldOnType(-1), s_italicOnType(-1), s_underlinedOnType(-1), s_strikeOnType(-1), s_subscriptOnType(-1), s_superscriptOnType(-1), s_bgOnType(), s_fgOnType(), s_fontTypeOnType("NO-CHANGE-ON-TYPE"),
    s_fontSizeOnType(-1)
{
    connect(s_clipboard,SIGNAL(dataChanged()),this,SLOT(updateState()));
    updateState();
}

void ISelection::updateState()
{
    emit canCutChanged(text()!="");
    emit boldChanged(bold());
    emit italicChanged(italic());
    emit underlinedChanged(underlined());
    emit strikeChanged(strike());
    emit subscriptChanged(subscript());
    emit superscriptChanged(superscript());
    emit bgChanged(background());
    emit fgChanged(foreground());
    emit fonttypeChanged(fonttype());
    emit fontsizeChanged(fontsize());
    emit textChanged();
}

/////////////////////////////////////////////////////////////////////
// CUT ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Cut::Cut(ISelection *parent) : s_parent(parent)
{
    s_cut=s_parent->text();
    s_oldClipboard=s_parent->s_clipboard->text();
    redo();
}
void ISelection::Cut::redo()
{
    s_parent->s_clipboard->setText(s_cut);
    s_parent->setText("");
    s_parent->updateState();
}
void ISelection::Cut::undo()
{
    s_parent->s_clipboard->setText(s_oldClipboard);
    s_parent->setText(s_cut);
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// COPY ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Copy::Copy(ISelection *parent) : s_parent(parent)
{
    s_copy=s_parent->text();
    s_oldClipboard=s_parent->s_clipboard->text();
    redo();
}
void ISelection::Copy::redo()
{
    s_parent->s_clipboard->setText(s_copy);
    s_parent->updateState();
}
void ISelection::Copy::undo()
{
    s_parent->s_clipboard->setText(s_oldClipboard);
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// PASTE ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Paste::Paste(ISelection *parent) : s_parent(parent)
{
    s_oldText=s_parent->text();
    s_paste=s_parent->s_clipboard->text();
    redo();
}
void ISelection::Paste::redo()
{
    if(s_paste.size()) {
        s_parent->setText(s_paste);
        s_parent->updateState();
    }
}
void ISelection::Paste::undo()
{
    if(s_paste.size()) {
        s_parent->setText(s_oldText);
        s_parent->updateState();
    }
}

/////////////////////////////////////////////////////////////////////
// BOLD ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Bold::Bold(ISelection *parent,bool bold) : s_parent(parent), s_bold(bold),s_oldBold(s_parent->s_document->s_bold)
{
    redo();
}
void ISelection::Bold::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_bold.set(s_parent->s_begin,s_parent->s_end,s_bold);
    } else {
        s_parent->s_boldOnType=s_bold;
    }
    s_parent->updateState();
}
void ISelection::Bold::undo()
{
    s_parent->s_document->s_bold=s_oldBold;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// ITALIC ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Italic::Italic(ISelection *parent,bool italic) : s_parent(parent), s_italic(italic),s_oldItalic(s_parent->s_document->s_italic)
{
    redo();
}
void ISelection::Italic::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_italic.set(s_parent->s_begin,s_parent->s_end,s_italic);
    } else {
        s_parent->s_italicOnType=s_italic;
    }
    s_parent->updateState();
}
void ISelection::Italic::undo()
{
    s_parent->s_document->s_italic=s_oldItalic;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// UNDERLINED ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Underlined::Underlined(ISelection *parent,bool underlined) : s_parent(parent), s_underlined(underlined),s_oldUnderlined(s_parent->s_document->s_underlined)
{
    redo();
}
void ISelection::Underlined::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_underlined.set(s_parent->s_begin,s_parent->s_end,s_underlined);
    } else {
        s_parent->s_underlinedOnType=s_underlined;
    }
    s_parent->updateState();
}
void ISelection::Underlined::undo()
{
    s_parent->s_document->s_underlined=s_oldUnderlined;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// STRIKE ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Strike::Strike(ISelection *parent,bool strike) : s_parent(parent), s_strike(strike), s_oldStrike(s_parent->s_document->s_strike)
{
    redo();
}
void ISelection::Strike::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_strike.set(s_parent->s_begin,s_parent->s_end,s_strike);
    } else {
        s_parent->s_strikeOnType=s_strike;
    }
    s_parent->updateState();
}
void ISelection::Strike::undo()
{
    s_parent->s_document->s_strike=s_oldStrike;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// SUBSCRIPT ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Subscript::Subscript(ISelection *parent,bool subscript) : s_parent(parent), s_subscript(subscript), s_oldSubscript(s_parent->s_document->s_subscript)
{
    redo();
}
void ISelection::Subscript::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_subscript.set(s_parent->s_begin,s_parent->s_end,s_subscript);
    } else {
        s_parent->s_subscriptOnType=s_subscript;
    }
    s_parent->updateState();
}
void ISelection::Subscript::undo()
{
    s_parent->s_document->s_subscript=s_oldSubscript;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// SUPERSCRIPT ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Superscript::Superscript(ISelection *parent,bool superscript) : s_parent(parent), s_superscript(superscript), s_oldSuperscript(s_parent->s_document->s_superscript)
{
    redo();
}
void ISelection::Superscript::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_superscript.set(s_parent->s_begin,s_parent->s_end,s_superscript);
    } else {
        s_parent->s_superscriptOnType=s_superscript;
    }
    s_parent->updateState();
}
void ISelection::Superscript::undo()
{
    s_parent->s_document->s_superscript=s_oldSuperscript;
    s_parent->updateState();
}


/////////////////////////////////////////////////////////////////////
// BACKGROUND ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Background::Background(ISelection *parent,QColor bg) : s_parent(parent), s_background(bg), s_oldBackground(s_parent->s_document->s_background)
{
    redo();
}
void ISelection::Background::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_background.set(s_parent->s_begin,s_parent->s_end,s_background);
    } else {
        s_parent->s_bgOnType=s_background;
    }
    s_parent->updateState();
}
void ISelection::Background::undo()
{
    s_parent->s_document->s_background=s_oldBackground;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// FOREGROUND ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Foreground::Foreground(ISelection *parent,QColor fg) : s_parent(parent), s_foreground(fg), s_oldForeground(s_parent->s_document->s_foreground)
{
    redo();
}
void ISelection::Foreground::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_foreground.set(s_parent->s_begin,s_parent->s_end,s_foreground);
    } else {
        s_parent->s_fgOnType=s_foreground;
    }
    s_parent->updateState();
}
void ISelection::Foreground::undo()
{
    s_parent->s_document->s_foreground=s_oldForeground;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// FONTTYPE ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Fonttype::Fonttype(ISelection *parent,QString ft) : s_parent(parent), s_fonttype(ft), s_oldFonttype(s_parent->s_document->s_fonttype)
{
    redo();
}
void ISelection::Fonttype::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_fonttype.set(s_parent->s_begin,s_parent->s_end,s_fonttype);
    } else {
        s_parent->s_fontTypeOnType=s_fonttype;
    }
    s_parent->updateState();
}
void ISelection::Fonttype::undo()
{
    s_parent->s_document->s_fonttype=s_oldFonttype;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// FONTSIZE ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Fontsize::Fontsize(ISelection *parent,int ft) : s_parent(parent), s_fontsize(ft), s_oldFontsize(s_parent->s_document->s_fontsize)
{
    redo();
}
void ISelection::Fontsize::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_parent->s_document->s_fontsize.set(s_parent->s_begin,s_parent->s_end,s_fontsize);
    } else {
        s_parent->s_fontSizeOnType=s_fontsize;
    }
    s_parent->updateState();
}
void ISelection::Fontsize::undo()
{
    s_parent->s_document->s_fontsize=s_oldFontsize;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// TEXT CHANGE ACTION
/////////////////////////////////////////////////////////////////////
ISelection::ChangeText::ChangeText(ISelection *parent,QString text) : s_parent(parent), s_txt(text), s_oldTxt(s_parent->text()), s_begin(s_parent->s_begin), s_end(s_parent->s_end)
{
    redo();
}
void ISelection::ChangeText::redo()
{
    if(s_begin!=s_end) {
        s_parent->s_document->remove(s_begin,s_end-s_begin);
        s_parent->setPos(s_begin);
    }
    s_parent->s_firstLine+=s_txt.count('\n');
    s_parent->s_lastLine=s_parent->s_firstLine;

    s_parent->s_document->insert(s_begin,s_txt);
    s_parent->s_end=s_parent->s_begin=s_begin+s_txt.length();

    if(s_parent->s_boldOnType!=-1) s_parent->s_document->s_bold.set(s_begin,s_begin+1,s_parent->s_boldOnType);
    if(s_parent->s_italicOnType!=-1) s_parent->s_document->s_italic.set(s_begin,s_begin+1,s_parent->s_italicOnType);
    if(s_parent->s_underlinedOnType!=-1) s_parent->s_document->s_underlined.set(s_begin,s_begin+1,s_parent->s_underlinedOnType);
    if(s_parent->s_strikeOnType!=-1) s_parent->s_document->s_strike.set(s_begin,s_begin+1,s_parent->s_strikeOnType);
    if(s_parent->s_subscriptOnType!=-1) s_parent->s_document->s_subscript.set(s_begin,s_begin+1,s_parent->s_subscriptOnType);
    if(s_parent->s_superscriptOnType!=-1) s_parent->s_document->s_superscript.set(s_begin,s_begin+1,s_parent->s_superscriptOnType);
    if(s_parent->s_fontSizeOnType!=-1) s_parent->s_document->s_fontsize.set(s_begin,s_begin+1,s_parent->s_fontSizeOnType);
    if(s_parent->s_bgOnType.isValid()) s_parent->s_document->s_background.set(s_begin,s_begin+1,s_parent->s_bgOnType);
    if(s_parent->s_fgOnType.isValid()) s_parent->s_document->s_foreground.set(s_begin,s_begin+1,s_parent->s_fgOnType);
    if(s_parent->s_fontTypeOnType!="NO-CHANGE-ON-TYPE") s_parent->s_document->s_fonttype.set(s_begin,s_begin+1,s_parent->s_fontTypeOnType);
    s_parent->s_boldOnType=s_parent->s_italicOnType=s_parent->s_underlinedOnType=s_parent->s_strikeOnType=s_parent->s_subscriptOnType=
            s_parent->s_superscriptOnType=s_parent->s_fontSizeOnType=-1;
    s_parent->s_bgOnType=s_parent->s_fgOnType=QColor();
    s_parent->s_fontTypeOnType="NO-CHANGE-ON-TYPE";
    s_parent->updateState();
}
void ISelection::ChangeText::undo()
{
    s_parent->s_document->remove(s_begin,s_txt.length());
    s_parent->s_document->insert(s_begin,s_oldTxt);
    s_parent->s_begin=s_begin;
    s_parent->s_end=s_end;
    s_parent->updateState();
}

void ISelection::ChangeText::cont(QString txt)
{
    Q_ASSERT(0);    // some work to be done

    if(txt==""&&s_begin+s_txt.size()) {
        s_txt.chop(1);
        s_parent->s_document->remove(s_begin+s_txt.size(),1);
    }
    if(s_begin!=s_end) {
        s_parent->s_document->remove(s_begin,s_end-s_begin);
    }
    s_parent->s_document->insert(s_begin+s_txt.size(),txt);
    s_txt+=txt;
    s_parent->s_end=s_parent->s_begin=s_begin+s_txt.length();

    if(s_parent->s_boldOnType!=-1) s_parent->s_document->s_bold.set(s_begin,s_begin+1,s_parent->s_boldOnType);
    if(s_parent->s_italicOnType!=-1) s_parent->s_document->s_italic.set(s_begin,s_begin+1,s_parent->s_italicOnType);
    if(s_parent->s_underlinedOnType!=-1) s_parent->s_document->s_underlined.set(s_begin,s_begin+1,s_parent->s_underlinedOnType);
    if(s_parent->s_strikeOnType!=-1) s_parent->s_document->s_strike.set(s_begin,s_begin+1,s_parent->s_strikeOnType);
    if(s_parent->s_subscriptOnType!=-1) s_parent->s_document->s_subscript.set(s_begin,s_begin+1,s_parent->s_subscriptOnType);
    if(s_parent->s_superscriptOnType!=-1) s_parent->s_document->s_superscript.set(s_begin,s_begin+1,s_parent->s_superscriptOnType);
    if(s_parent->s_fontSizeOnType!=-1) s_parent->s_document->s_fontsize.set(s_begin,s_begin+1,s_parent->s_fontSizeOnType);
    if(s_parent->s_bgOnType.isValid()) s_parent->s_document->s_background.set(s_begin,s_begin+1,s_parent->s_bgOnType);
    if(s_parent->s_fgOnType.isValid()) s_parent->s_document->s_foreground.set(s_begin,s_begin+1,s_parent->s_fgOnType);
    if(s_parent->s_fontTypeOnType!="NO-CHANGE-ON-TYPE") s_parent->s_document->s_fonttype.set(s_begin,s_begin+1,s_parent->s_fontTypeOnType);
    s_parent->s_boldOnType=s_parent->s_italicOnType=s_parent->s_underlinedOnType=s_parent->s_strikeOnType=s_parent->s_subscriptOnType=
            s_parent->s_superscriptOnType=s_parent->s_fontSizeOnType=-1;
    s_parent->s_bgOnType=s_parent->s_fgOnType=QColor();
    s_parent->s_fontTypeOnType="NO-CHANGE-ON-TYPE";
    s_parent->updateState();
}

ISelection::RemoveText::RemoveText(ISelection *parent) : s_parent(parent), s_begin(s_parent->s_begin), s_end(s_parent->s_end)
{
    if(s_parent->s_begin!=s_parent->s_end) {
        s_oldTxt=s_parent->text();
    } else {
        s_oldTxt=s_parent->s_document->s_string[s_begin-1];
    }

    redo();
}
void ISelection::RemoveText::redo()
{
    if(s_parent->s_begin!=s_parent->s_end) {
        qDebug()<<s_parent->s_firstLine<<"!";
        s_parent->setPos(s_begin);
        qDebug()<<s_parent->s_firstLine<<"!<";
        s_parent->s_document->remove(s_begin,s_end-s_begin);
    } else {
        s_parent->setPos(s_begin-1);
        s_parent->s_document->remove(s_begin-1,1);
        this->s_parent->s_begin=this->s_parent->s_end=s_begin-1;
    }
//    s_parent->s_firstLine+=s_txt.count('\n');
//    s_parent->s_lastLine=s_parent->s_firstLine;

    s_parent->updateState();
}
void ISelection::RemoveText::undo()
{
    if(s_begin!=s_end) {
        s_parent->s_document->insert(s_begin,s_oldTxt);
    } else {
        s_parent->s_document->insert(s_begin-1,s_oldTxt);
    }
    s_parent->s_begin=s_begin;
    s_parent->s_end=s_end;
    s_parent->updateState();
}

/////////////////////////////////////////////////////////////////////
// ALIGN ACTION
/////////////////////////////////////////////////////////////////////
ISelection::Align::Align(ISelection *parent,IString::Alignment align) : s_parent(parent), s_align(align), s_oldAlign(s_parent->s_document->s_align)
{
    qDebug()<<s_parent->s_firstLine<<s_parent->s_lastLine;
    redo();
}
void ISelection::Align::redo()
{
    s_parent->s_document->s_align.set(s_parent->s_firstLine,s_parent->s_lastLine+1,s_align);
    s_parent->updateState();
}
void ISelection::Align::undo()
{
    s_parent->s_document->s_align=s_oldAlign;
    s_parent->updateState();
}
