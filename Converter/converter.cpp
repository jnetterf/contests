// (C) Joshua Netterfield 2009

#include "converter.h"

Converter::Converter() {
    for (int i = 0; i < 2; i++)
        rootConversionElement[i] = new ConversionElement;
}

Converter::Converter( QString filename, QString cTableFilename ) {
    for (int i = 0; i < 2; i++)
        rootConversionElement[i] = new ConversionElement;
    setFilename(filename);
    setCTableFilename(cTableFilename);
}

Converter::~Converter() {
}

void Converter::setFilename( QString file ) {
    filename = file;
}

void Converter::setCTableFilename( QString cTable ) {
    cTableFilename = cTable;
}

void Converter::convert() {
    loadConversions();
    //QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(loadDocument()));
    //timer->start(1);
    loadDocument();
    //testCTable ( rootConversionElement[0] );
}

/* ~ public slots ~ */

bool Converter::loadDocument() {
    /* Load in the kst 1.x (input) file */
    oldDoc = new QDomDocument("kst 1.x XML");
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        cout << "You are attempting to convert a file which does not exist or otherwise cannot be read.\n";
        return false;
    }
    if (!oldDoc->setContent(&file)) {
        cout << "You are attempting to convert a file which is probably not from kst 1.3, or even an XML file!\n";
        file.close();
        return false;
    }
    file.close();

    if (oldDoc->documentElement().attributeNode("version").value() != "1.3") {
        cout << "You are attempting to convert a file which is not from kst 1.3, which is not supported.\n";
        return false;
    }

    /* Create a new kst 2.0 output xml */
    newDoc = new QDomDocument();
    QDomElement root = newDoc->createElement( "?xml" );
    root.setAttribute( "version", "1.0" );
    root.setAttribute( "encoding", "UTF-8" );
    newDoc->appendChild(root);

    QDomElement b = newDoc->createElement( "kst" );
    b.setAttribute( "version", "2.0" );
    QDomElement rootb = newDoc->firstChildElement();

    root.appendChild( b );

    convertElement( oldDoc->documentElement().firstChildElement(), rootConversionElement[0] );
    cout << qPrintable( newDoc->toString() );
    return true;
}

/* ~ private ~ */

void Converter::testCTable(ConversionElement *x) {
    if ( x->root.size() > 8.5)
        cout << qPrintable( x->root ) << "\t" << qPrintable( x->charData ) << "\t";
    else
        cout << qPrintable( x->root ) << "\t\t" << qPrintable( x->charData ) << "\t";

    QStringList hiarchy;
    if ( x->hasTwin == true ) {
        ConversionElement *t = x->getTwin();
        ConversionElement *u = t;
        while ( t->hasParent == true ) {
            t = t->getParent();
            hiarchy.prepend( t->root );
        }
        for ( int i = 1; i < hiarchy.size(); i++ ) {    // i = 1 to ignore the very root.
            cout << qPrintable( hiarchy[i] ) << "\t";
        }
        cout << qPrintable( u->root ) << "\t" << qPrintable( u->charData );

        for ( int h = 0 ; h < 2; h++ ) {
            for ( int i = 0 ; i < u->getPropertyLength() ; i++ ) {
                cout << "\n\t" << qPrintable( u->getPropertyName(i) ) << "\t" << qPrintable( u->getPropertyValue(i) );
            }
            cout << endl;
            u = x;
        }
    }
    cout << endl;
    QList<ConversionElement *> *children = x->getChildren();
    for (int i = 0; i < children->size(); i++) {
        testCTable( (*children)[i] );
    }
}

void Converter::loadConversions() {
    if (cTableFilename == "")
        cTableFilename = "convert_table.dat";

    QFile file( cTableFilename );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int h[2] = { -1, -1 };                                        // previous indentation. 4 is a tab.
    ConversionElement *p[2];
    p[0] = rootConversionElement[0];   // previous element
    p[1] = rootConversionElement[1];   // previous element

    while (!file.atEnd()) {
        QString ln = file.readLine();
        if (ln[0] != '#' && ln != "" && ln.length() > 2 ) {
            int i = 0;
            for ( int j = 0; j <= 1; j++ ) {
                if ( ln == "" )
                    break;
                ConversionElement *c;   //current element.
                while (ln[i] == ' ')
                    i++;
                if ( j == 0 ) {
                    if (h[j] >= i) {
                        p[j] = p[j]->getParent();
                    }
                    while (h[j] > i) {
                        h[j] -= 4; //tab is -4
                        p[j] = p[j]->getParent();
                    }
                    c = new ConversionElement(p[j]);   // if (h[j] < i) is a child of previous.
                    // if (h[j] = i) is a sibling of previous.
                    // if (h[j] > i) is a sibling of a (grand-)parent of previous
                    h[j] = i;
                    p[j] = c;
                } else {
                    ln.remove(0, i);
                    i = 0;

                    c = rootConversionElement[1];
                    if (QString::compare(ln, "IGNORE") == 1 ) {
                        c = new ConversionElement(c);
                        c->root = "IGNORE";
                        c->setTwin( p[0] );
                        p[j] = c;
                        break;
                    } else {
                        int k = 0;
                        while ( 1 ) {
                            int tmp = 0;
                            k = 0;
                            while ( ( tmp = ln.indexOf("<", tmp ) ) != -1 ) {
                                ++tmp;
                                k++;
                            }
                            
                            if ( k <= 1 )
                                break;

                            
                            ln.remove( 0, 1 );
                            
                            QString root = ln.left( ln.indexOf( ">", 0 ) );
                            ln.remove(0, ln.indexOf( ">", 0) +1 );
                            c = c->getChild(root);
                        }
                        c = new ConversionElement(c);
                        c->setTwin( p[0] );
                        p[j] = c;
                    }
                }
                bool isTagName=false, isPropertyName=false, isPropertyDef=false, isData=false;
                QString tagName, propertyName, propertyDef, data;

                while ( i < ln.length() ) {
                    if (ln[i] == '#') {
                        break;
                    } else if (isPropertyName) {
                        if ( ln[i] == '=' ) {
                            isPropertyName = false;
                            isPropertyDef = true;
                            i++;    // this way we ignore the " :)
                        } else {
                            propertyName += ln[i];
                        }
                    } else if (isPropertyDef) {
                        if ( ln[i] == '\"' ) {
                            p[j]->addProperty( propertyName, propertyDef );
                            propertyName = "";
                            propertyDef = "";
                            isPropertyDef = false;
                        } else {
                            propertyDef += ln[i];
                        }
                    } else if (isTagName) {
                        if (ln[i] == '>') {
                            if (p[j]->root == "")
                                p[j]->root = tagName;
                            tagName = "";
                            isTagName = false;
                            // else will capture data next if it is data.
                        }
                        else if (ln[i] == ' ') {
                            if (j == 1 && ( QString::compare(tagName, "NEW") == 1 || QString::compare(tagName, "NEW") == 0 ) ) {
                                p[j]->addProperty( "NEW", "" );
                                tagName = "";
                                // Do not add space.
                            } else
                                isPropertyName = true;
                        }
                        else if (ln[i] != '/')
                            tagName += ln[i];
                    } else if (isData) {
                        if (ln[i] == '<') {
                            p[j]->charData = data;
                            data = "";
                            i--;    // so that tag name captures it next.
                            isData = false;
                        } else {
                            data += ln[i];
                        }
                    } else if (ln[i] == '<') {
                        isTagName = true;
                    } else if (ln[i] == ' ') {
                        break;
                    } else {
                        i--;    // so that data doesn't loose a char.
                        isData = true;
                    }
                    i++;
                }
            }
        }
    }
}

void Converter::convertElement(const QDomElement &element, ConversionElement *c) {
    QDomElement b = element;
    while(!b.isNull()) {
        if ( c->hasChild( b.tagName() ) ) {
            // Get the element we are converting, and it's 2.x twin.
            ConversionElement *o = c->getChild( b.tagName() );
            ConversionElement *p = o->getTwin();

            if ( p->root.compare("IGNORE") != 0 ) {
                // Get the hiarchy of the 2.x version, and append the hiarchy if non-existant. Make q the element we are modifying.
                QDomElement q = newDoc->firstChildElement();
                QStringList hiarchy = p->getHiarchy();
                for ( int i = 0 ; i < hiarchy.length() ; i++ ) {
                    if ( q.elementsByTagName( hiarchy[i] ).length() == 0 ) {
                        QDomElement newChild = newDoc->createElement( hiarchy[i] );
                        q.appendChild( newChild );
                    }
                    q = q.elementsByTagName( hiarchy[i] ).at( q.elementsByTagName( hiarchy[i] ).length()-1 ).toElement();
                }

                // Create the element if it is either unexistant or the NEW property is set. Otherwise give us the element

                QDomElement newElement;

                if ( q.elementsByTagName( p->root ).length() == 0 || p->hasProperty( "NEW" ) ) {
                    newElement = newDoc->createElement( p->root );
                    q.appendChild( newElement );
                } else {
                    newElement = q.elementsByTagName( p->root ).at( q.elementsByTagName( p->root ).length()-1 ).toElement();
                }

                // Set variables from text of old QDomElement

                if ( b.firstChild().toText().data().length() != 0 && o->charData.length() != 0) {
                    QString varName = o->charData;
                    varName.remove( 0, 1 );             // NOTE: This is where we will check for %/^ !!!

                    QString varValue = b.firstChild().toText().data();
                    this->variables[0] << varName;
                    this->variables[1] << varValue;
                }

                // Set variables from properties of old QDomElement

                for ( uint i = 0 ; i < b.attributes().length() ; i++ ) {
                    if ( o->hasProperty( b.attributes().item( i ).toAttr().name() ) ) {
                        QString varName = o->getPropertyValue( b.attributes().item( i ).toAttr().name() );
                        varName.remove( 0, 1 );
                        variables[0] << varName;
                        variables[1] << b.attributes().item( i ).toAttr().value();
                    } else {
                        cout << "WARNING! Variable " << qPrintable( b.attributes().item( i ).toAttr().name() )
                                << " is not defined in " << qPrintable( cTableFilename ) << endl;
                    }
                }

                // Assign variables to text of new QDomElement

                if ( p->charData.length() != 0 ) {
                    QString propName = p->charData;
                    propName.remove( 0, 1 );             // NOTE: This is where we will check for % or ^ !!!

                    if ( variables[0].lastIndexOf( propName ) != -1 ) {
                        int x = variables[0].lastIndexOf( propName );

                        newElement.setAttribute( variables[0][x], variables[1][x] );

                    }
                }

                // Assign variables to properties of new QDomElement

                for ( int i = 0 ; i < p->getPropertyLength() ; i++ ) {
                    QString propName = p->getPropertyValue( i );
                    propName.remove(0, 1);  // THIS IS WHERE WE CHECK

                    if ( variables[0].lastIndexOf( propName ) != -1 ) {
                        int x = variables[0].lastIndexOf( propName );

                        QString varName = p->getPropertyName( i );

                        newElement.setAttribute( varName, variables[1][x] );
                    } else {
                        // Provide a warning...
                    }
                }

                // Convert elements of children ( converts first child and all of it's siblings. )
                convertElement( b.firstChildElement(), o );
            }
        } else {
            //cout << "Warning! " << qPrintable( b.tagName() ) << " is not defined in "
            //        << qPrintable( cTableFilename ) << endl;
        }
        b = b.nextSiblingElement();
    }
}
