
    for ( int i = 0; i < _unplacedBeats.size(); i++ ) {
        if ( i != 0 ) {
            double a = _unplacedBeats.at(i-1)->startTime();
            double b = _unplacedBeats.at(i)->startTime();
            a+=0.0625;
            while( a < b ) {
                std::cerr << a << " " << 0 << std::endl;
                a+=0.0625;
            }
        }
        std::cerr << _unplacedBeats.at(i)->startTime() << " " << _unplacedBeats.at(i)->summativeVelocity() << std::endl;
    }
