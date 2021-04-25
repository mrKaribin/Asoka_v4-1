#ifndef ADJECTIVE_H
#define ADJECTIVE_H

#include "word.h"


class Adjective : public Word
{
public:
    Adjective(astring _text) : Word(_text, AssistentTypes::Adjective)
    {

    }

private:

};

#endif // ADJECTIVE_H
