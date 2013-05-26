#include "iparagraph.h"
#include <aspell.h>
#include <cstdio>

AspellConfig* IParagraph::s_spellConfig=0;
AspellCanHaveError* IParagraph::s_canHaveError;
AspellSpeller* IParagraph::s_spellChecker;
std::bitset<13> IParagraph::s_defaultBitset;

IParagraph::IParagraph() : s_indent(1), s_alignment(Left), s_listType(None), s_number(-1), s_dirty(1), s_locked(0) {
    if(!s_spellConfig) {
        s_spellConfig=new_aspell_config();
        aspell_config_replace(s_spellConfig, "lang", "en_US");

        s_canHaveError = new_aspell_speller(s_spellConfig);
        s_spellChecker = 0;
        if (aspell_error_number(s_canHaveError) != 0) puts(aspell_error_message(s_canHaveError));
        else s_spellChecker = to_aspell_speller(s_canHaveError);
    }

    s_defaultBitset[Bold]=0;
    s_defaultBitset[Italic]=0;
    s_defaultBitset[Underline_A]=0;
    s_defaultBitset[Underline_B]=0;
    s_defaultBitset[Underline_C]=0;
    s_defaultBitset[Underline_D]=0;
    s_defaultBitset[Underline_E]=0;
    s_defaultBitset[Underline_F]=0;
    s_defaultBitset[Underline_G]=0;
    s_defaultBitset[Underline_H]=0;
    s_defaultBitset[SuperOrSubScript]=0;
    s_defaultBitset[Subscript]=0;
    s_defaultBitset[SpellingCorrect]=1;
}

IParagraph::~IParagraph() {

}

void IParagraph::setGeometry(std::map<int,int> &geometry) {
    s_geometry=geometry;
    s_dirty=1;
}

void IParagraph::checkSpelling() {
    assert(!s_locked);
    lock();
    s_locked=0; //hack!
    s_format.s_locked=0; //hack

    do setFormatElement<SpellingCorrect>(1); while(next());
    while(prev());

    char cache[45]; //Pneumonoultramicroscopicsilicovolcanoconiosis is the longest word en anglais and is 45 characters long, so I don't think the spellchecker is going to help us beyond that length.
    for(int i=0;i<45;++i) cache[i]='\0';

    int l=-1;
    do {
        if( l<45&&(cache[++l]=getChar())==' ' ) {
            cache[l]='\0';
            bool correct = aspell_speller_check(s_spellChecker, cache, -1);
            setFormatElement<SpellingCorrect>(1);
            for(int i=0;i<l;++i) {
                prev();
                setFormatElement<SpellingCorrect>(correct);
            }
            for(int i=0;i<l;i++) next();
            l=-1;
        }
    } while(next());


    s_format.s_locked=1; //hack
    s_locked=1; //hack!
    unlock();
}
