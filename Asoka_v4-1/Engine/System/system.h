#ifndef SYSTEM_H
#define SYSTEM_H

#include "acore.h"
#include "lcore.h"


class System
{
public:
    void initialize()
    {

    }

    static AIdentifier& createIdentifier(void* _object, astring _name = DEFAULT_OBJECT_NAME)
    {
        return ACore::identifier_create(_object, _name);
    }

    static LShape& linkShapeToObject(LShape _shape)
    {

    }

    static LFunctional& link(LShape& shape, Verb word, LFunctional functional)
    {
        LAction* action = new LAction(word);
        QVector<LObject*> lobjects = shape.mainObjects();
        if(lobjects.size() == 1)
        {

        }
        else
            Asoka::Log::warn(logPage, "");
    }


private:
    struct ObjectData
    static QHash<LShape*, AIdentifier*> objects;
    static

    static Asoka::Log::Page& logPage;
};

#endif // SYSTEM_H
