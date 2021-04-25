#pragma once
#include <string>

#include "System/system.h"

using namespace std;


class AObject
{
public:
    AObject(AObject* _parent = nullptr, astring _name = DEFAULT_OBJECT_NAME, LShape _shape = LShape())
        : id(System::createIdentifier(this, _name)),
          shape(System::linkShapeToObject(_shape))
    {
        parent = _parent;
    }
    

    AObject* getParent()
    {
        return parent;
    }

    LShape getShape() const
    {
        return shape;
    }
    
    bool existParent()
    {
        if(parent == NULL)
            return false;
        else
            return true;
    }
    
    void setParent(AObject* _parent)
    {
        parent = _parent;
    }
    
    void removeParent()
    {
        parent = NULL;
    }

    void tester(int seconds)
    {
        while (seconds != 0)
        {
            cout << endl << seconds << " seconds remaining...";
            this_thread::sleep_for(std::chrono::seconds(1));
            seconds--;
        }
    }


    AIdentifier&            id;
    LShape&                 shape;
    
private:
    AObject*                parent;
};
