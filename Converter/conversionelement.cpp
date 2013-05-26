// (C) Joshua Netterfield 2009

#include "conversionelement.h"

ConversionElement::ConversionElement(ConversionElement *parent) {
    if (parent != 0) {
        hasParent = true;
        this->parent = parent;
        parent->addChild(this);
    } else
        hasParent = false;
    children = new QList<ConversionElement *>;
    hasTwin = false;
}

void ConversionElement::addChild(ConversionElement *child) {
    *children << child;
}

ConversionElement* ConversionElement::getParent() {
    if (hasParent == true)
        return parent;
    else
        return 0;
}

QStringList ConversionElement::getHiarchy( QStringList *list ) {
    if (hasParent == true) {
        list->prepend( parent->root );
        parent->getHiarchy( list );
    }
    return *list;
}

QList<ConversionElement *>* ConversionElement::getChildren(QString rootFilter, QString propertyFilter) {
    return children;
}

ConversionElement * ConversionElement::getChild(QString rootFilter) {
    for ( int i = 0 ; i < children->length() ; i++ ) {
        if ( (*children)[i]->root == rootFilter )
            return (*children)[i];
    }

    ConversionElement * newChild = new ConversionElement( this );
    newChild->root = rootFilter;
    return newChild;
}

bool ConversionElement::hasChild(QString rootFilter) {
    for ( int i = 0 ; i < children->length() ; i++ ) {
        if ( (*children)[i]->root == rootFilter )
            return true;
    }

    return false;
}

void ConversionElement::addProperty(QString name, QString value) {
    propertyNames << name;
    propertyValues << value;
}

QString ConversionElement::getPropertyName( int i ) {
    return propertyNames[i];
}

QString ConversionElement::getPropertyValue( int i ) {
    return propertyValues[i];
}

QString ConversionElement::getPropertyValue( QString name ) {
    for ( int i = 0; i < getPropertyLength(); i++) {
        if ( getPropertyName(i) == name )
            return propertyValues[i];
    }
    return NULL;
}

int ConversionElement::getPropertyLength() {
    return propertyNames.size();
}

bool ConversionElement::hasProperty(QString name) {
    for ( int i = 0; i < getPropertyLength(); i++) {
        if ( getPropertyName(i) == name )
            return true;
    }
    return false;
}

void ConversionElement::setTwin(ConversionElement *twin, bool recurse) {
    hasTwin = true;
    this->twin = twin;
    if (recurse)
        twin->setTwin(this, false);
}

ConversionElement * ConversionElement::getTwin() {
    return twin;
}
