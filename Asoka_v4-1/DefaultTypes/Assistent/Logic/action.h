#ifndef ACTION_H
#define ACTION_H

#include "lelement.h"
#include "DefaultTypes/Assistent/Linguistics/verb.h"

#include <QVector>


class LAction : public LElement
{
public:
    LAction(Verb _word) : LElement(_word, AssistentTypes::Action)
    {

    }

    QJsonObject toJson() override
    {

    }

    void fromJson(QJsonObject _object) override
    {

    }

private:

};

#endif // ACTION_H
