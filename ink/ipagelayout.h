#ifndef IPAGELAYOUT_H
#define IPAGELAYOUT_H

#include <QObject>

// Just a dummy for now.
class IPageLayout : public QObject
{
    Q_OBJECT
    double s_width, s_height, s_topM, s_botM, s_leftM, s_rightM;
public:
    IPageLayout(QObject* parent);
    /** Returns the width of all pages in the current document, in inches. */
    double width() { return s_width; }

    /** Returns the height of all pages in the current document, in inches. */
    double height() { return s_height; }

    /** Returns the top margins of all pages in the current document, in inches. */
    double topmargin() { return s_topM; }
    /** Returns the bottom margins of all pages in the current document, in inches. */
    double bottommargin() { return s_botM; }
    /** Returns the left margins of all pages in the current document, in inches. */
    double leftmargin() { return s_leftM; }
    /** Returns the right margins of all pages in the current document, in inches. */
    double rightmargin() { return s_rightM; }

public slots:
    void setWidth(double width) { s_width=width; emit layoutChanged(); }
    void setHeight(double height) { s_height=height; emit layoutChanged(); }
    void setTopMargin(double top) { s_topM=top; emit layoutChanged(); }
    void setBottomMargin(double bottom) { s_botM=bottom; emit layoutChanged(); }
    void setLeftMargin(double left) { s_leftM=left; emit layoutChanged(); }
    void setRightMargin(double right) { s_rightM=right; emit layoutChanged(); }

signals:
    void layoutChanged();
};

#endif // IPAGELAYOUT_H
