#pragma once
#include "lelement.h"
#include "property.h"
#include "action.h"
#include "DefaultTypes/Assistent/Linguistics/noun.h"

#include <QVector>


class LObject : public LElement
{
public:
    LObject(Noun _word) : LElement(_word, AssistentTypes::Object)
    {

    }

    LObject(Noun _word, QList<LProperty*> _properties, QList<LAction*> _actionsExecuting, QList<LAction*> _actionsApplied)
        : LElement(_word, AssistentTypes::Object)
    {
        properties = _properties;
        actionsExecuting = _actionsExecuting;
        actionsApplied = _actionsApplied;
    }

    QJsonObject toJson() override
    {

    }

    void fromJson(QJsonObject _object) override
    {

    }

    QList<LProperty*> getProperties() const
    {
        return properties;
    }

    QList<LAction *> getActionsExecuting() const
    {
        return actionsExecuting;
    }

    QList<LAction *> getActionsApplied() const
    {
        return actionsApplied;
    }

private:
    QList<LProperty*> properties;
    QList<LAction*> actionsExecuting;
    QList<LAction*> actionsApplied;
};
