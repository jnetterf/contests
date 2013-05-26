#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include "iparagraph.h"

class IDocument
{
    IUniqueContainer<IParagraph> s_paragraphs;
    IContainer<std::bitset<2> > s_space;   // Before, After
public:
    IDocument();
};

#endif // IDOCUMENT_H
