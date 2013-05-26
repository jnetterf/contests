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

int denForNum( int num ) {
    if ( num == 3 ) return 4;
    if ( num == 4 ) return 4;
    if ( num == 5 ) return 4;
    if ( num == 6 ) return 8;
    if ( num == 7 ) return 4;
    if ( num == 11 ) return 8;
}

double closestRatio( double aprox ) {
    //std::cerr << aprox;
    QList< double > ratios;
    ratios << 0 << 0.41504 << 0.58496
           << 1 << 1.41504 << 1.58496
           << 2 << 2.41504 << 3.58496
           << 3 << 3.41504 << 3.58496
           << 4 << 4.41504 << 4.58496
           << 5 << 5.41504 << 5.58496
           << 6 << 6.41504 << 6.58496;

    for ( int i = 1; i < ratios.size(); i++ ) if ( ratios[i-1] <= aprox && aprox <= ratios[i] ) {

        if ( fabs( aprox - ratios[i-1] ) < fabs( aprox - ratios[i] ) ) return fabs( ratios[i-1] );
        else return fabs( ratios[ i ] );

    }
    return -100;
}

int main() {    
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "CAN'T OPEN FILE!\n";
        return -255;
    }

    double lastDouble = 0;

    QList< double > x_;
    QList< double > y_;
    QList< double > velocity;

    QString c;
    while (!file.atEnd()) {
        QString line = file.readLine();

        QString b = line;
        b.truncate( line.indexOf(' '));

        QString magic = line;
        magic.chop( 1 );
        magic.remove(0, line.indexOf(" ")+1 );
        velocity.append( magic.toDouble() );

        line.remove( line.indexOf(' '), 383912801 );
        if ( lastDouble == 0 ) {
            lastDouble = line.toDouble();
            c = b;
            continue;
        }
        double a = line.toDouble();
        x_.append( c.toDouble() );
        y_.append( log2( a-lastDouble ));
        c = b;
        lastDouble = line.toDouble();
    }

    QList< double > x;
    QList< double > y;

    bool ok = false;

    double lowest = 9999;
    double highest= -1;
    double l = 0.01;
    double lastlb = 0, lasthb = 0;
    int tryNo = 0;

    // try to rotate it, but don't fuss if it can't.
    while ( !ok ) {
        if ( ++tryNo == 6000 ) {
            ok = true;
            l = 0;
        }
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

    int bins = rint( ( highest-lowest )*48.0384 );  // I forget where I got this number, but it's really smart! I promise!
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

    QList< double > last;

    for ( int i = 1; i <= noteID; i++ ) {
        int count = 0;
        double sum = 0;
        int velocityT = 0;
        for ( int j = y.size()/2; j < y.size(); j++ ) {
            if ( y_[j] == i ) {
                count++;
                sum += yuncorrected[j];
                velocityT += velocity[j];
            }
        }
        last.append( sum/count );
        //std::cerr << i << " " << sum/count << std::endl;
    }

    QList< double > currentDif;
    QList< double > correctDif;
    for ( int i = 1; i < last.size(); i++ ) currentDif.append( last[ i ] - last[ i-1 ] );
    for ( int i = 0; i < currentDif.size(); i++ ) {
        correctDif.append( closestRatio( currentDif[i] ) );
    }
    for ( int i = 1; i < last.size(); i++ ) {
        last[ i ] = last[ i-1 ] + correctDif[i-1];
    }

    QList< double > beatCandidats;
    for ( int i = 0; i < last.size(); i++ ) {
        beatCandidats << exp2( last[i] ) << exp2( last[i] -1 );
    }

    double tm = 0;
    QList< double > newX;
    for ( int i = 0; i < y_.size(); i++ ) {
        newX.append( tm );
        tm += exp2( last[ y_[i]-1 ] );
    }

    // try random stuff very inefficiently
    QList< int > bcHits;
    QList< int > phase;
    for ( int i = 0; i < beatCandidats.size(); i++ ) {
        QList< int > phaseHits;
        double tnow;
        for ( int j = 0; j < 20 && j < newX.size(); j++ ) {
            phaseHits.append( 0 );
            tnow = newX[j];
            int w = 0;
            for ( double k = tnow; k < newX.last() - 0.005; k += beatCandidats[i] ) {
                while ( newX[w] - 0.00001 < k ) {  // :) yay!
                    if ( newX[w] - 0.00001 < k && newX[w] + 0.00001 > k ) phaseHits.last()++;
                    w++;
                }
            }
        }
        int highest = 0;
        int highestW;
        for ( int w = 0; w < phaseHits.size(); w++ ) {
            if ( phaseHits[w] > highest ) {
                highest = phaseHits[w];
                highestW= w;
            }
        }
        bcHits.append( highest );
        std::cerr << "!" << bcHits.last() << std::endl;
        phase.append( highestW );
    }

    for ( int i = 0; i< 0; i++ ) {} // !?

    int highestV = 0;
    double highestBC = 0;
    int highestP = 0;
    for ( int p = 0; p < bcHits.size(); p++ ) {
        std::cerr << bcHits[p] << " IS " << (double)60/beatCandidats[p] << std::endl;
        if ( bcHits[p] > highestV || ( bcHits[p] == highestV && beatCandidats[p] > highestBC ) ) {
            highestV = bcHits[p];
            highestBC = beatCandidats[p];
            highestP = p;
        }
    }

    std::cerr << "PULSE IS " << (double)60/highestBC << std::endl;

    ///////////////////////////////////////////////////////////////////

    bool done = false;
    bool doneCLOOP = true;
    int factor = 1;
    int oldFactor = 1;
    int numLCD = 1;
    while ( !done && doneCLOOP ) {

        doneCLOOP = false;
        QList< double > standardDeviations;
        QList< int > lowest;
        QList< int > highest;
        for ( int c = 2; c < 20 && c < newX.size() && !doneCLOOP; c++ ) {
            int summativeVelocities[c];
            for ( int i = 0; i < c; i++ ) summativeVelocities[i] = 0;

            int w = 0;
            int ci = 0;
            for ( double k = 0; k < newX.last() - 0.005; k += highestBC*factor ) {
                while ( newX[w] - 0.00001 < k ) {  // :) yay!
                    if ( newX[w] - 0.00001 < k && newX[w] + 0.00001 > k ) {
                        summativeVelocities[ci] += velocity[w];
                    }
                    w++;
                }
                ci++;
                if ( ci == c ) ci = 0;
            }
         //   std::cerr << std::endl << c << ":";

            int sum = 0;
            int tlowest = 999999; int thighest = 0;
            for ( int i = 0; i < c; i++ ) {
                sum += summativeVelocities[i];
                if ( summativeVelocities[i] < tlowest ) tlowest = summativeVelocities[i];
                if ( summativeVelocities[i] > thighest ) thighest = summativeVelocities[i];
           //     std::cerr << summativeVelocities[i] << " ";
            }
            standardDeviations.append( sqrt( sum/c ));

            if ( ( thighest - tlowest ) / standardDeviations.last()  >  15 ) {
                std::cerr << "!!" << c << std::endl;
                oldFactor = factor;
                factor *= c;
                if ( numLCD != 2 ) numLCD *= c;
                else numLCD = c;
                doneCLOOP = true;
                continue;
            }

            //std::cerr << std::endl;

        }
    }

    // FIXES FOR ISSUES.

    // 4 will register itself as 2
    if ( numLCD == 2 ) numLCD = 4;

    // sometimes 4/4 bars are patterns of 8/8
    if ( factor == 8 ) { factor /= 2; oldFactor *= 2; }

    // DEFINITIONS

    if ( numLCD == 6 ) oldFactor /= 3;  // unit is quarter note note, not dotted half note.
    //else if ( numLCD == 9 ) oldFactor /= ;
    //else if ( numLCD ==12 ) oldFactor /= ;

    std::cerr << "The tempo might be " << (double)60/highestBC / oldFactor << " in " << numLCD << "/" << denForNum( numLCD ) << " or it might not." << std::endl;

    //for ( int i = 0; i < standardDeviations.size(); i++ ) std::cerr << i << "::" << standardDeviations[i] << std::endl;
    // IDS
    //for ( int i = 0; i < y_.size(); i++ ) {
    //  std::cerr << time << " " << velocity[i] << std::endl;
    //}

    //for ( int i = 0; i < y_.size(); i++ ) {
//        std::cerr << x[i] << " " << last[ y_[i]-1 ] << std::endl;
//    }
}

