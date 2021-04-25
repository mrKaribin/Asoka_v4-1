#ifndef LELEMENT_H
#define LELEMENT_H

#include "DefaultTypes/Assistent/Linguistics/word.h"

#include <QJsonObject>

class LShape;


namespace AssistentTypes
{
    enum LogicType {Action = 1, Object, Property};
}


class LElement
{
public:
    LElement(Word _word, AssistentTypes::LogicType _type) : word(_word)
    {
        type = _type;
    }

    Word getWord() const
    {
        return word;
    }

    AssistentTypes::LogicType getType()
    {
        return type;
    }

    virtual QJsonObject toJson() = 0;

    virtual void fromJson(QJsonObject _object) = 0;

private:
    Word word;
    AssistentTypes::LogicType type;
};

#endif // LELEMENT_H
