#ifndef PROPERTY_H
#define PROPERTY_H

#include "lelement.h"
#include "DefaultTypes/Assistent/Linguistics/adjective.h"


class LProperty : public LElement
{
public:
    LProperty(Adjective _word) : LElement(_word, AssistentTypes::Property)
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


#endif // PROPERTY_H
