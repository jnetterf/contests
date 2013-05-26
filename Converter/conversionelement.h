// (C) Joshua Netterfield 2009

#ifndef CONVERSIONELEMENT_H
#define CONVERSIONELEMENT_H

#include <QList>
#include <QString>
#include <QStringList>

class ConversionElement;

class ConversionElement {
public:
    ConversionElement(ConversionElement *parent = 0);

    ConversionElement* getParent();
    QStringList getHiarchy(QStringList *list = new QStringList);

    void addChild(ConversionElement *child);
    QList<ConversionElement *>* getChildren(QString rootFilter = "", QString propertyFilter = "");
    ConversionElement * getChild(QString rootFilter);
    bool hasChild( QString rootFilter );

    void addProperty(QString name, QString value);
    QString getPropertyName( int i );
    QString getPropertyValue( int i );
    QString getPropertyValue( QString name );
    int getPropertyLength();
    bool hasProperty( QString name );

    void setTwin(ConversionElement *twin, bool recurse = true);
    ConversionElement *getTwin();

    QString root;
    QString charData;

    bool hasParent;
    bool hasTwin;
private:
    ConversionElement *parent;
    QList<ConversionElement *> *children;

    ConversionElement *twin;    // The twin in the kst 1.x/2.x world.

    QList<QString> propertyNames;
    QList<QString> propertyValues;
};

#endif // CONVERSIONELEMENT_H
