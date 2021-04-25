#pragma once
#include "asoka.h"
#include "DefaultTypes/Assistent/Logic/shape.h"

#define DEFAULT_IDENTIFIER()

using namespace std;

using identifier = vector <bit8>;


class AIdentifier
{
public:
    AIdentifier(void* _object, identifier _id, astring _name = DEFAULT_OBJECT_NAME)
    {
        arr_id.resize(_id.size());
        arr_id = _id;
        fld_name = _name;
        fld_object = _object;
    }

    bool operator == (const AIdentifier& _id)
    {
        if (arr_id == _id.id())
            return true;
        else
            return false;
    }

    bool operator == (const identifier _id)
    {
        if (arr_id == _id)
            return true;
        else
            return false;
    }

    bool operator == (const astring _name)
    {
        if (fld_name == _name)
            return true;
        else
            return false;
    }

    const identifier id() const
    {
        return arr_id;
    }

    astring name() const
    {
        return fld_name;
    }

    void* object() const
    {
        return fld_object;
    }

private:

    identifier          arr_id;
    void*               fld_object;
    astring             fld_name;
};
