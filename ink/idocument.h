#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include "istring.h"
#include "iselection.h"
#include "ipagelayout.h"

#include <QWidget>
#include <QMap>
#include <QPoint>
#include <QList>

class IDocument : public QWidget
{
    Q_OBJECT
    friend class IRibbon;
    IString* s_str;
    ISelection* s_select;
    IPageLayout* s_layout;
    int s_i;
    int s_origPos;

    /* MOUSE TRACKING */
        QMap<int,int> s_cacheY; /* ENDING Y CORD -> LINE NUMBER */
        QList< QMap<int,int> > s_cacheX; /* FOR EACH LINE, STARTING X CORD -> LETTER */

    QList<int> s_tabStops;

    /* KEY */
        int s_cursorX,s_cursorY;

public slots:
    void testUpdate();  //depricate later....
public:
    IDocument(QWidget* parent);
    int textPosForGeoPos(int x,int y,int offset=0) const;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

protected:
    bool event(QEvent *);
    void keyPressEvent(QKeyEvent *);
};

#endif // IDOCUMENT_H
