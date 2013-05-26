#include <iostream>
#include "iparagraph.h"

int main() {
        IParagraph p;
    for(int i=0;i<20000;i++) {
        if(i) {
            IAction::globalUndo();
            IAction::globalUndo();
            IAction::globalUndo();
        }
        p.insertChars_action(L"Testing");
        p.prev_action(7);
//        p.insertChars_action(L"Falala");
//        p.setFormatElements<IParagraph::Bold>(std::make_pair(1,1));
        p.setFormatElements_action<IParagraph::Bold>(1,3);
        p.next_action(7);

    }
    std::cerr<<"\n\n";
    p.lock();
    do std::cerr<<(bool)p.getFormatElement<IParagraph::Bold>(); while(p.next());
    std::cerr<<'|'<<std::endl;
    p.unlock();
    p.s_str.gotoStart();
}
