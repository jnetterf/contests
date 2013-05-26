// (C) Joshua Netterfield 2009

#ifndef CONVERTER_H
#define CONVERTER_H

#include <iostream>
using namespace std;
#include <QFile>
#include <QTimer>
#include <QStringList>
#include <QDomDocument>
#include <QtCore/QCoreApplication>

#include <conversionelement.h>

class Converter //: public QObject
{
//Q_OBJECT
public:
    Converter();
    Converter( QString filename, QString cTable = "" );
    ~Converter();
    void setFilename( QString file );
    void setCTableFilename( QString cTable );
    void convert();

public slots:
    bool loadDocument();

private:

    void testCTable(ConversionElement *x);

    void loadConversions();
    void convertElement( const QDomElement &element, ConversionElement *c );
    QString filename;
    QString cTableFilename;

    QStringList variables[2];

    QDomDocument *oldDoc;
    QDomDocument *newDoc;

    ConversionElement *rootConversionElement[2];
};

#endif // CONVERTER_H
