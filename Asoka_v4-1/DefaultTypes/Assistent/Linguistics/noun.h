#pragma once
#include "word.h"
#include "morpheme_analyzer.h"


class Noun : public Word
{
public:
	Noun(astring _text) : Word(_text, AssistentTypes::WordType::Noun)
	{
		
    }

    AssistentTypes::Gender getGender()
	{
        return gender;
	}

    AssistentTypes::Number getNumber()
	{
        return number;
	}

private:
	static AssistentTypes::Gender spotGender(astring _word)
	{
        
	}

	static AssistentTypes::Number spotNumber(astring _word)
	{
        
	}

	static Noun get(astring _word, AssistentTypes::Gender _gender, AssistentTypes::Number _number = AssistentTypes::Singular)
	{
        using namespace AssistentTypes;
        StemmerPorterResult word_reduced = StemmerPorter::reduce(_word);
		if(_gender == Masculine && _gender == Feminine && word_reduced.deleted == "")
            int i = 10;
	}

    AssistentTypes::Gender gender;
    AssistentTypes::Number number;

};
