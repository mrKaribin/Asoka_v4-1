#ifndef SHAPE_H
#define SHAPE_H

#include "object.h"
#include "functional.h"

#include <QVector>
#include <QJsonObject>


class LShape
{
public:
    LShape()
    {

    }

    LShape(QVector<LObject*> _objects)
    {
        for(auto object : _objects)
            append(object);
    }

    LShape(QJsonObject _object)
    {
        fromJson(_object);
    }

    void append(LObject* _object)
    {
        objects.append(_object);
        properties.append(_object->getProperties());
        actions.append(_object->getActionsExecuting());
        actions.append(_object->getActionsApplied());
    }

    void append(LAction* _action)
    {
        actions.append(_action);
    }

    void append(LProperty* _property)
    {
        properties.append(_property);
    }

    QVector<LObject*> mainObjects()
    {

    }

    QJsonObject toJson()
    {

    }

    void fromJson(QJsonObject object)
    {

    }

    static LShape toShape(LObject* object)
    {
        LShape result;
        result.append(object);
        return result;
    }

private:
    QList<LObject*> objects;
    QList<LAction*> actions;
    QList<LProperty*> properties;
};

#endif // SHAPE_H
