#include <iostream>
#include <QtCore/QCoreApplication>
#include <QFile>
#include <QList>
#include <math.h>

/*
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "CAN'T OPEN FILE!\n";
        return -255;
    }

    double lastDouble = 0;

    int i = 0;

    QString c;
    while (!file.atEnd()) {
        QString line = file.readLine();

        QString b = line;
        b.truncate( line.indexOf(' '));

        line.remove( line.indexOf(' '), 383912801 );
        if ( lastDouble == 0 ) {
            lastDouble = line.toDouble();
            c = b;
            continue;
        }
        double a = line.toDouble();
        std::cerr << c.toStdString() << " " << a-lastDouble << std::endl;
        c = b;
        lastDouble = line.toDouble();
    }

    //return a.exec();
}*/

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "CAN'T OPEN FILE!\n";
        return -255;
    }

    QList< double > x_;
    QList< double > y_;

    QString c;
    while (!file.atEnd()) {
        QString a = file.readLine();
        QString b = a;
        b.truncate( a.indexOf(" ") );
        a.chop( 1 );
        a.remove(0, a.indexOf(" ")+1 );

        x_.append( b.toDouble() );
        y_.append( log2( a.toDouble() ) );
    }

    QList< double > x;
    QList< double > y;

    bool ok = false;

    double lowest = 9999;
    double highest= -1;
    double l = 0.01;
    double lastlb = 0, lasthb = 0;

    while ( !ok ) {
        x = x_;
        y = y_;
        lowest = 9999;
        highest= -1;
        foreach( double a, y ) {
            if ( a < lowest ) lowest = a;
            if ( a > highest) highest= a;
        }

        for ( int i = 0; i < y.size(); i++ ) {
            y[i] += l*i;
        }
        l -= 0.00001;

        double lowestb = 9999;
        double highestb= -1;
        foreach( double a, y ) {
            if ( a < lowestb ) lowestb = a;
            if ( a > highestb) highestb= a;
        }
        if ( ( highestb-lowestb ) < ( highest - lowest ) && ( lasthb - lastlb ) < ( highestb - lowestb ) ) {
            lowest = lowestb;
            highest = highestb;
            ok = true;
        }
        lastlb = lowestb;
        lasthb = highestb;
    }
    QList< double > yuncorrected = y_;
    y_ = y;
    QList< double > ybk = y;
    x_ = x;

    qSort( y );

    // create histogram...

    int bins = rint( ( highest-lowest )*48.0384 );
    int bina = 0;

    int j = -1;
    int count[bins];
    for ( int i = 0; i < bins; i++ ) count[i] = 0;

    for ( int i = 0; i < 61; i++ ) {
        double T = lowest + (highest-lowest)/bins * (double)(i+1);
        if ( j+1 < y.size() && T > y[j+1] ) bina++;
        while ( ++j < y.size() && T > y[j] ) count[i]++;
        j--;
    }

    std::cerr << bina << "/" << bins << "!\n";
    for ( int i = 0; i < bins; i++ ) {
        std::cerr << count[i] << " ";
    }

    int goodCount = 0;
    int fixed = 0;
    int noteID = 0;
    for ( int i = 0; i < bins; i++ ) {
        if ( count[i] == 0 ) goodCount++;   // FIX ME:: CREATE ALTERNATIVES
        else goodCount = 0;

        if ( goodCount == 10 || i == bins-1 ) {
            noteID++;
            double Tmax = lowest + (highest-lowest)/bins * (double)(i+1);
            double Tmin = lowest + (highest-lowest)/bins * (double)(fixed);
            for ( int j = 0; j < y_.size(); j++ ) {
                //std::cerr << Tmin << " " << Tmax << " " << y_[j] << std::endl;
                if ( Tmin <= y_[j] && y_[j] <= Tmax ) y_[j] = noteID;
            }
            fixed = i;
        }
    }

    std::cerr << std::endl << highest << " " << lowest << std::endl;

    for ( int i = 1; i <= noteID; i++ ) {
        int count = 0;
        double sum = 0;
        for ( int j = 0; j < y.size(); j++ ) {
            if ( y_[j] == i ) {
                count++;
                sum += yuncorrected[j];
            }
        }
        std::cerr << "!!" << i << ":" << sum/count << std::endl;
    }

    // IDS
    //for ( int i = 0; i < y_.size(); i++ ) {
    //    std::cerr << x[i] << " " << y_[i] << std::endl;
    //}

    
    //return a.exec();
}

