#pragma once
#include <iostream>
#include <functional>
#include <QMutex>
#include <QFunctionPointer>

using function = QFunctionPointer;


template <class TYPE>
class Object
{
public:
	Object()
	{
		clear();
	}

	Object(TYPE* _object)
	{
		set(_object);
	}

	const Object& operator = (TYPE* _object)
	{
		set(_object);
		return *this;
	}

	TYPE& operator () ()
	{
		return *fld_object;
	}

	const Object& set(TYPE* _object)
	{
		fld_object = _object;
		return *this;
	}

	const Object& clear()
	{
		if (fld_object != NULL)
			delete fld_object;
		fld_object = NULL;
		return *this;
	}

	bool exist()
	{
		if (fld_object == NULL)
			return false;
		else
			return true;
	}

private:
	TYPE* fld_object;
};


template <class TYPE>
class Data
{
public:
	Data()
	{
		clear();
	}

	Data(TYPE* _object)
	{
		set(_object);
	}

	const Data& operator = (TYPE* _object)
	{
		set(_object);
		return *this;
	}

	const Data& operator = (TYPE _object)
	{
		set(_object);
		return *this;
	}

	TYPE& operator () ()
	{
		return *fld_object;
	}

	const Data& lock()
	{
        fld_access->lock();
		return *this;
	}

	bool locked()
	{
        bool _locked = fld_access->try_lock();
		if (_locked)
            fld_access->unlock();
		return _locked;
	}

	bool tryLock()
	{
        return fld_access->try_lock();
	}

	const Data& unlock()
	{
        fld_access->unlock();
		return *this;
	}

	const Data& set(TYPE* _object)
	{
        fld_access->lock();
		fld_object = _object;
        fld_access->unlock();
		return *this;
	}

	const Data& set(TYPE _object)
	{
        fld_access->lock();
		*fld_object = _object;
        fld_access->unlock();
		return *this;
	}

	TYPE& get()
	{
        fld_access->lock();
		return *fld_object;
	}

	const Data& clear()
	{
		if (fld_object != NULL)
			delete fld_object;
		fld_object = NULL;
		return *this;
	}

	bool exist()
	{
		if (fld_object == NULL)
			return false;
		else
			return true;
	}

private:
    QMutex* fld_access = new QMutex;
	TYPE* fld_object;
};


template <class TYPE, class ... ARGS>
class AFunction
{
public:

    AFunction(TYPE (*_function)(ARGS ...))
	{
        fld_function = _function;
	}

	AFunction(const AFunction& func)
	{
		fld_function = func.to_function();
	}


    TYPE (*to_function())(ARGS ...)
	{
		return fld_function;
	}

	TYPE run(ARGS ... args) const
	{
		return fld_function(args ...);
	}

private:
    TYPE (*fld_function)(ARGS ...) = NULL;

};


template <class OBJECT, class TYPE, class ... ARGS>
class AMethod
{
public:

    AMethod(OBJECT* object, TYPE (OBJECT::*method)(ARGS ...))
	{
		fld_object = object;
		fld_method = method;
	}

    AMethod(OBJECT* object, std::function <TYPE(OBJECT&, ARGS ...)> method)
    {
        fld_object = object;
        fld_method = method;
    }

	AMethod(const AMethod& method)
	{
		fld_object = (OBJECT*)method.object();
		fld_method = method.to_function();
	}


    OBJECT& object() const
	{
		return fld_object;
	}

    std::function <TYPE(OBJECT&, ARGS ...)> to_function()
	{
		return fld_method;
	}

	TYPE run(ARGS ... args) const
	{
		return fld_method(*fld_object, args ...);
	}

private:

    OBJECT* fld_object = NULL;
    //TYPE (OBJECT::*fld_method)(ARGS ...);
    std::function <TYPE(OBJECT&, ARGS ...)> fld_method;

};
