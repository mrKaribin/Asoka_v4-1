#pragma once
#include "word.h"


class Verb : public Word
{
public:
    Verb(astring _text) : Word(_text, AssistentTypes::Verb)
    {

    }

private:

};
