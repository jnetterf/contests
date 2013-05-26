#include "idocument.h"
#include <QPainter>
#include <QDebug>
#include <QFont>
#include <QApplication>
#include <QKeyEvent>
#include <QBrush>
#include <qmath.h>
#include <QtTest/QTest>
IDocument::IDocument(QWidget *parent) : QWidget(parent), s_str(new IString), s_select(new ISelection(this,s_str)), s_layout(new IPageLayout(this))
{
    QCursor c=cursor();
    c.setShape(Qt::IBeamCursor);
    setCursor(c);
    connect(s_select,SIGNAL(textChanged()),this,SLOT(testUpdate()));
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
//    setAutoFillBackground(1);
    s_i=0;
}


////////////////////////////////////////////////////////////////////////////////////////////
// PAINT
////////////////////////////////////////////////////////////////////////////////////////////

typedef  void (QFont::*QFontBoolMemFn)(bool truth);
typedef  void (QFont::*QFontStringMemFn)(const QString& str);
typedef  void (QFont::*QFontIntMemFn)(int z);

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
#define NEXT_CHAR() do foreach(AbstractMetaTextTrace* x, _ft) ++(*x); while(0)
#define PUSH_SETTINGS() do foreach(AbstractMetaTextTrace* x, _ft) x->push(); while(0)
#define POP_SETTINGS() foreach(AbstractMetaTextTrace* x, _ft) x->pop(); while(0)

class AbstractMetaTextTrace {
public:
    virtual void operator++() =0;
    virtual void push() {
        s_push_cur=s_cur;
        s_push_off=s_off;
    }
    virtual void pop()=0;

protected:
    AbstractMetaTextTrace() : s_cur(0), s_off(-1) {}
    int s_cur, s_off;
    int s_push_cur, s_push_off;
};

template < class T, class U > class MetaFontTrace : public AbstractMetaTextTrace {
    IMetaText<T>& s_data;
    U s_memFunc;
    QFont& s_font;
    QPainter& s_p;
    QFontMetrics& s_metrics;
public:
    MetaFontTrace(IMetaText<T>& data,U func, QFont& font,QPainter& p,QFontMetrics& metrics) : s_data(data), s_memFunc(func), s_font(font), s_p(p),
        s_metrics(metrics) {CALL_MEMBER_FN(s_font,s_memFunc)(s_data.s_elements[0].value);s_p.setFont(s_font);s_metrics=QFontMetrics(s_font);}
    inline void operator++() {
        if(++s_off==s_data.s_elements[s_cur].offset) {
            CALL_MEMBER_FN(s_font,s_memFunc)(s_data.s_elements[++s_cur].value);
            s_off=0;
            s_p.setFont(s_font);
            s_metrics=QFontMetrics(s_font);
        }
    }

    void pop() {
        s_cur=s_push_cur;
        s_off=s_push_off;
        CALL_MEMBER_FN(s_font,s_memFunc)(s_data.s_elements[s_cur].value);
        s_p.setFont(s_font);
        s_metrics=QFontMetrics(s_font);
    }
};

template < class T > class MetaLocalTrace : public AbstractMetaTextTrace {
    IMetaText<T>& s_data;
    T& s_local;
public:
    MetaLocalTrace(IMetaText<T>& data,T& local) : s_data(data), s_local(local) {s_local=s_data.s_elements[0].value;}
    inline void operator++() {
        if(++s_off==s_data.s_elements[s_cur].offset) {
            s_local=s_data.s_elements[++s_cur].value;
            s_off=0;
        }
    }
    void pop() {
        s_cur=s_push_cur;
        s_off=s_push_off;
        s_local=s_data.s_elements[s_cur].value;
    }
};

class PainterPenTrace : public AbstractMetaTextTrace {
    IMetaText<QColor>& s_data;
    QPainter& s_p;
public:
    PainterPenTrace(IMetaText<QColor>& data,QPainter& p) : s_data(data),s_p(p) { s_p.setPen(QPen(s_data.s_elements[0].value)); }
    inline void operator++() {
        if(++s_off==s_data.s_elements[s_cur].offset) {
            s_p.setPen(s_data.s_elements[++s_cur].value);
            s_off=0;
        }
    }
    void pop() {
        s_cur=s_push_cur;
        s_off=s_push_off;
        s_p.setPen(s_data.s_elements[s_cur].value);
    }
};

class PainterBrushTrace : public AbstractMetaTextTrace {
    IMetaText<QColor>& s_data;
    QPainter& s_p;
public:
    PainterBrushTrace(IMetaText<QColor>& data,QPainter& p) : s_data(data),s_p(p) { s_p.setBrush(QBrush(s_data.s_elements[0].value)); }
    inline void operator++() {
        if(++s_off==s_data.s_elements[s_cur].offset) {
            s_p.setBrush(s_data.s_elements[++s_cur].value);
            s_off=0;
        }
    }
    void pop() {
        s_cur=s_push_cur;
        s_off=s_push_off;
        s_p.setBrush(s_data.s_elements[s_cur].value);
    }
};

inline int calcNextWidth(const QCharRef& c,QList<int>& stops,const int& x,const IString::Alignment& align,QFontMetrics&fm,bool& subscript,bool& superscript,int asw=0)
{
    if(c=='\t') {
        switch(align)
        {
        case IString::Center:       // Fallback
        case IString::Justified:    // Eventually Justified text and centered text should make use of tab stops...
            return fm.width(' ')*5.0*((subscript||superscript)?0.65:1.0);
            break;
        case IString::Left:
            for(int i=0;i<stops.size();i++) {
                if(stops[i]>x) {
                    return stops[i]-x;
                }
            }
            return 999999;  // >_<
            break;
        case IString::Right:
            for(int i=stops.size()-1;i>=0;i--) {
                if(stops[i]<x) return x-stops[i];
            }
            return 999999;
            break;
        }
    } else {
        return fm.width(c)*((subscript||superscript)?0.65:1.0)+((c==' ')?asw:0);
    }
    Q_ASSERT(0);
    return -1;
}

/** Accepts: _ft, line, availWidth, fm
  * Returns: line (!!), width, height, remainingText
  */
void getLineInfo(std::vector<AbstractMetaTextTrace*>& _ft, QString&line, const int&availWidth, QFontMetrics&fm, int &width, int&height, int&descent, QString&remainingText,
                 bool&subScript,bool&superScript,QList<int>&stops,const IString::Alignment& align,const int& start)
{
    width=0;
    height=fm.height();
    descent=fm.descent();
    remainingText="";
    int j;

    PUSH_SETTINGS();

    int lastSpace=-1;
    int widthAtLastSpace;

    int nextWidth;
    for(j=0;j<line.size();j++) {
        NEXT_CHAR();

        if(!j&&line[j]==' ') nextWidth=0;
        else nextWidth=calcNextWidth(line[j],stops,start+width,align,fm,subScript,superScript);

        if(width+nextWidth>availWidth) break;
        if(line[j]==' ') {
            lastSpace=j;
            widthAtLastSpace=width;
        }

        width+=nextWidth;

        height=qMax(height,fm.height());
        descent=qMax(descent,fm.descent());
    }

    if(j!=line.size()&&lastSpace!=-1&&lastSpace!=0) {
        j=lastSpace;
        width=widthAtLastSpace;
    }
    remainingText=line;
    line.truncate(j);
    remainingText.remove(0,j);

    POP_SETTINGS();
}

void IDocument::paintEvent(QPaintEvent*pev)
{
    double dpiX=logicalDpiX();
    double dpiY=logicalDpiY();
    int pixX=dpiX*s_layout->width();
    int minX=(width()-pixX)/2;

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(pev->rect().x()+minX,pev->rect().y(),pixX,pev->rect().height(),QColor("white"));

    QFont font=QApplication::font();
    QFontMetrics fm(font);
    std::vector<AbstractMetaTextTrace*> _ft;

    bool subScript,superScript;

    _ft.push_back(new MetaFontTrace<bool,QFontBoolMemFn>(s_str->s_bold,&QFont::setBold,font,p,fm));
    _ft.push_back(new MetaFontTrace<bool,QFontBoolMemFn>(s_str->s_italic,&QFont::setItalic,font,p,fm));
    _ft.push_back(new MetaFontTrace<bool,QFontBoolMemFn>(s_str->s_underlined,&QFont::setUnderline,font,p,fm));
    _ft.push_back(new MetaFontTrace<bool,QFontBoolMemFn>(s_str->s_strike,&QFont::setStrikeOut,font,p,fm));
    _ft.push_back(new MetaFontTrace<QString,QFontStringMemFn>(s_str->s_fonttype,&QFont::setFamily,font,p,fm));
    _ft.push_back(new MetaFontTrace<int,QFontIntMemFn>(s_str->s_fontsize,&QFont::setPointSize,font,p,fm));
    _ft.push_back(new MetaLocalTrace<bool>(s_str->s_subscript,subScript));
    _ft.push_back(new MetaLocalTrace<bool>(s_str->s_superscript,superScript));
    _ft.push_back(new PainterPenTrace(s_str->s_foreground,p));
    _ft.push_back(new PainterBrushTrace(s_str->s_background,p));

    p.setFont(font);

    QStringList a=s_str->s_string.split('\n');
    int _Y_=fm.height()+s_layout->topmargin()*dpiY;
    int _T_=0;
    int _C_=s_select->s_begin;

    int _CHARNO_=0;

    int vIg=0;

    s_cacheY.clear();
    s_cacheX.clear();

    int _realLINE_=0;

    //TAB STOPS
    s_tabStops.clear();
    int lastTabStop=-1;
    while(1) {
        int next=minX+s_layout->leftmargin()*dpiX+(++lastTabStop)*0.5*dpiX;
        if(next>minX+s_layout->width()*dpiX) break;
        s_tabStops.push_back(next);
    }

    for(int i=0;i<a.size();i++) {
        _C_--;
        int _X_=minX+s_layout->leftmargin()*dpiX;
        int lW,lH,lD;
        QString remText;

        getLineInfo(_ft,a[i],pixX-s_layout->rightmargin()*dpiX-s_layout->leftmargin()*dpiX,fm,lW,lH,lD,remText,subScript,superScript,s_tabStops,s_str->s_align.get(_realLINE_+1),_X_);
        _Y_+=lH-lD;
        s_cacheY.insert(_Y_,_CHARNO_);
        s_cacheX.push_back(QMap<int,int>());

        double additionalSpaceWidth=0;
        int firstSpaceWidth=0;

        switch (s_str->s_align.get(_realLINE_+1)) {
        case IString::Left:
            //nothing to do here!
            break;
        case IString::Center:
            _X_+=(pixX-s_layout->rightmargin()*dpiX-s_layout->leftmargin()*dpiX-lW)/2;
            break;
        case IString::Right:
            _X_+=(pixX-s_layout->rightmargin()*dpiX-s_layout->leftmargin()*dpiX-lW);
            break;
        case IString::Justified:
            additionalSpaceWidth=(double)(pixX-s_layout->rightmargin()*dpiX-s_layout->leftmargin()*dpiX-lW)/((double)a.at(i).count(' ')-((a[i][0]==' ')?1.0:0.0)-((a[i].size()&&a[i][a[i].size()-1]==' ')?1.0:0.0));
            firstSpaceWidth=(double)(pixX-s_layout->rightmargin()*dpiX-s_layout->leftmargin()*dpiX-lW)-((double)(int)additionalSpaceWidth)*((double)a.at(i).count(' ')-((a[i][0]==' ')?1.0:0.0)-((a[i].size()&&a[i][a[i].size()-1]==' ')?1.0:0.0) );
            break;
        }
        additionalSpaceWidth=(int)additionalSpaceWidth;

        if(remText.size()) {a.insert(i+1,remText);++vIg;}

        int lineX=-1,lineY,lineX2,lineY2;

        if(_T_==_C_+1) {
            lineX=_X_;
            lineY=_Y_-lH+lD;
            lineX2=_X_;
            lineY2=_Y_+lD;
            s_cursorX=_X_;
            s_cursorY=_Y_-(lH+lD)/2;
        }

        for(int j=0;j<a[i].size();j++) {
            if(j+1==a[i].size()) additionalSpaceWidth=0.0;
            NEXT_CHAR();
            if(_T_==_C_)
            {
                lineX=_X_+calcNextWidth(a[i][j],s_tabStops,_X_,s_str->s_align.get(_realLINE_+1),fm,subScript,superScript,additionalSpaceWidth+(firstSpaceWidth?1:0));
//                if(a[i][j]=='\t') lineX=_X_+((j||a[i][j]!=' ')?fm.width(' ')*5:0);
//                else lineX=_X_+((j||a[i][j]!=' ')?fm.width(a[i][j]):0);
                lineY=_Y_-lH+lD;
                lineX2=_X_+calcNextWidth(a[i][j],s_tabStops,_X_,s_str->s_align.get(_realLINE_+1),fm,subScript,superScript,additionalSpaceWidth+(firstSpaceWidth?1:0));
//                if(a[i][j]=='\t') lineX2=_X_+((j||a[i][j]!=' ')?fm.width(' ')*5:0);
//                else lineX2=_X_+((j||a[i][j]!=' ')?fm.width(a[i][j]):0);
                lineY2=_Y_+lD;
                s_cursorX=_X_;
                s_cursorY=_Y_-(lH+lD)/2;
            }
            QPen curPen=p.pen();
            QBrush curBrush=p.brush();
            if(s_select->s_begin!=s_select->s_end&&s_select->s_begin<=_CHARNO_&&s_select->s_end>_CHARNO_) {
                QColor c=curBrush.color();
                c.setRed(255-c.red());
                c.setBlue(255-c.blue());
                c.setGreen(255-c.green());
                p.fillRect(_X_,_Y_-lH+lD,calcNextWidth(a[i][j],s_tabStops,_X_,s_str->s_align.get(_realLINE_+1),fm,subScript,superScript),lH,c);
                QColor c2=curPen.color();
                c2.setRed(255-c2.red());
                c2.setBlue(255-c2.blue());
                c2.setGreen(255-c2.green());
                p.setPen(c2);
            } else {
                p.fillRect(_X_,_Y_-lH+lD,calcNextWidth(a[i][j],s_tabStops,_X_,s_str->s_align.get(_realLINE_+1),fm,subScript,superScript),lH,curBrush);
            }
            if(j||a[i][j]!=' ') {
                if(subScript||superScript) {
                    QFont f=p.font();
                    QFont fb=f;
                    fb.setPointSizeF(fb.pointSizeF()*0.65);
                    p.setFont(fb);
                    p.drawText(_X_,_Y_-(double)lH*(subScript?-0.141:0.35),QString(a[i][j]));
                    p.setFont(f);
                    s_cacheX.back().insert(_X_,_CHARNO_);
                    _X_+=calcNextWidth(a[i][j],s_tabStops,_X_,s_str->s_align.get(_realLINE_+1),fm,subScript,superScript,additionalSpaceWidth+(firstSpaceWidth?1:0));
                } else {
                    p.drawText(_X_,_Y_,QString(a[i][j]));
                    s_cacheX.back().insert(_X_,_CHARNO_);
                    _X_+=calcNextWidth(a[i][j],s_tabStops,_X_,s_str->s_align.get(_realLINE_+1),fm,subScript,superScript,additionalSpaceWidth+(firstSpaceWidth?1:0));
                }
            }
            if(a[i][j]==' '&&firstSpaceWidth>0) firstSpaceWidth--;
            p.setPen(curPen);
            _CHARNO_++;
            ++_T_;
        }
        if(lineX!=-1) {
            p.setPen(QPen("black"));
            p.drawLine(lineX,lineY,lineX2,lineY2);
        }

        if(!vIg) { // Ignore '\n'
            ++_realLINE_;
            NEXT_CHAR();
            ++_CHARNO_;
        } else {
            ++_C_;
            --vIg;
        }
    }
    p.end();

    while(_ft.size()) { delete _ft.back(); _ft.pop_back(); }
}

int IDocument::textPosForGeoPos(int x,int y,int offset) const
{
    int i,j,k;

    for(i=0;i<s_cacheY.size();i++) if(s_cacheY.keys()[i]>=y) break;
    i+=offset;
    while(i>=s_cacheX.size()) {--i; }
    while(i<0) { ++i; }
    for(j=0;j<s_cacheX[i].size();j++) if(s_cacheX[i].keys()[j]>x) return s_cacheX[i].values()[j];
    for(k=0;i-k>=0;k++) if(s_cacheX[i-k].size()) return s_cacheX[i-k].values().last()+1+k;
    return s_str->s_string.size();
}

bool IDocument::event(QEvent *e)
{
    if(e->type()==QEvent::KeyPress) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(e);
        keyPressEvent(ke);
        return 1;
    } else return QWidget::event(e);
}

void IDocument::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_Backspace:
        s_select->backspace();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        s_select->setText("\n");
        break;
    case Qt::Key_Left:
        s_select->goLeft(e->modifiers()&Qt::ShiftModifier);
        break;
    case Qt::Key_Right:
        s_select->goRight(e->modifiers()&Qt::ShiftModifier);
        break;
    case Qt::Key_Up:
        s_select->setPos(textPosForGeoPos(s_cursorX,s_cursorY,-1),e->modifiers()&Qt::ShiftModifier);
        break;
    case Qt::Key_Down:
        s_select->setPos(textPosForGeoPos(s_cursorX,s_cursorY,1),e->modifiers()&Qt::ShiftModifier);
        break;
    case Qt::Key_Home:
        s_select->setPos(textPosForGeoPos(0,s_cursorY,0),e->modifiers()&Qt::ShiftModifier);
        break;
    case Qt::Key_End:
        s_select->setPos(textPosForGeoPos(999999,s_cursorY,0),e->modifiers()&Qt::ShiftModifier);
        break;
    case Qt::Key_Tab:
        s_select->setText("\t");
        break;
    default:
        QString t=e->text();
        if(t!="") s_select->setText(t);
    }
}

void IDocument::mousePressEvent(QMouseEvent *e)
{
    s_origPos=textPosForGeoPos(e->x(),e->y());
    if(s_origPos==-1) return;
    else s_select->setPos(s_origPos);
}

void IDocument::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons()&Qt::LeftButton&&s_origPos!=-1) {
        int i=textPosForGeoPos(e->x(),e->y());
        int j=s_origPos;
        s_select->setPos(qMin(i,j));
        s_select->setPos(qMax(i,j),1);
    }
}

void IDocument::testUpdate()
{
    update();
}
