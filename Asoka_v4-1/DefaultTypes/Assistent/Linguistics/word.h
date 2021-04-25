#pragma once
#include "types.h"
#include "DefaultTypes/astring.h"


class Word
{
public:
	Word(astring _text, AssistentTypes::WordType _type)
	{
		text = _text;
		type = _type;
    }


    int getId() const
    {
        return id;
    }

    astring getText() const
    {
        return text;
    }

    AssistentTypes::WordType getType() const
    {
        return type;
    }

private:
    int id = 0;
    astring text = 0;
    AssistentTypes::WordType type;
};

/*
class PartOfSpeech : public Word
{
public:
	PartOfSpeech(astring _text, WordType _type) : Word(_text, _type)
	{

	}

private:
	Gender
};
*/
