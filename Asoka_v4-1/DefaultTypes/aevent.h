#pragma once

#include "Engine/System/acore.h"

using namespace std;

enum ConnectionType {Connection_Immediate, Connection_Multithreaded, Connection_Unary};


template<typename ... T>
void ignored(T ...) { ; }


template <class RETURN, class ... ARGS>
class Connector
{
public:
	Connector(ConnectionType _type)
	{
		type = _type;
	}

	ConnectionType type; 
    std::function <RETURN(ARGS ...)> receiver;
};

template <class RETURN, class ... ARGS >
class AActivator
{
public:
    AActivator(astring _name = "") : id(ACore::identifier_create(this, _name))
    {
		AActivator& _event = *this;
		fld_function = [&_event](ARGS ... args) -> std::vector <RETURN>
		{
			vector <RETURN> arr_return;
			for (auto connector : _event.receivers())
			{
				RETURN returned;
				if(connector->type == Connection_Immediate)
					returned = connector->receiver(args ...);
				arr_return.push_back(returned);
			}
			return arr_return;
		};
	}

	using connector = Connector<RETURN, ARGS ...>;

	RETURN operator () (ARGS ... args)
	{
		return fld_function(args ...);
	}

	vector <connector*> receivers()
	{
		return arr_connectors;
	}

private:
	AIdentifier& id;
    std::function <RETURN(ARGS ...)> fld_function;
	vector <connector*> arr_connectors;
}; 


template <class ... ARGS>
class AEvent
{
public:
    AEvent(astring _name = DEFAULT_OBJECT_NAME) : id(ACore::identifier_create(this, _name))
    {
		AEvent& _event = *this;
		fld_function = [&_event](ARGS ... args)
		{
			for (auto connector : _event.receivers())
			{
				connector->receiver(args ...);
			}
			_event.receive = [args ...](ARGS& ... _args)
			{
				ignored(_args = args ...);
			};
			_event.private_is_Emited();
		};
	}

	using connector = Connector<void, ARGS ...>;

	void operator () (ARGS ... args)
	{
		fld_function(args ...);
	}

	template <class OBJECT>
    void receivers_add(OBJECT* object, std::function <void (OBJECT&, ARGS ...)> _function, ConnectionType type = Connection_Immediate)
	{
		connector* new_connector = new connector(type);
		OBJECT& _object = *object;
		AEvent& _event = *this;
		connector& _receiver = *new_connector;
		switch (type)
		{
		case Connection_Immediate:
			new_connector->receiver = [&_object, _function](ARGS ... args)
			{
				_function(_object, args...);
			};
			break;
		case Connection_Multithreaded:
			new_connector->receiver = [&_object, _function](ARGS ... args)
			{
				thread new_thread([&_object, _function, args ...]() {_function(_object, args...); });
			};
			break;
		case Connection_Unary:
			new_connector->receiver = [&_event, &_receiver, &_object, _function](ARGS ... args)
			{
				_function(_object, args...);
				_event.receivers_remove(&_receiver);
			};
			break;
		default:
			break;

		}
		arr_receivers.push_back(new_connector);
	}

	template <class OBJECT>
	void receivers_add(AMethod <OBJECT, void, ARGS ...> method, ConnectionType type = Connection_Immediate)
	{
		receivers_add(method.object(), method.to_function(), type);
	}

    void receivers_add(std::function <void(ARGS ...)> _function, ConnectionType type = Connection_Immediate)
	{
		connector* new_connector = new connector(type);
		AEvent& _event = *this;
		connector& _receiver = *new_connector;
		switch (type)
		{
		case Connection_Immediate:
			new_connector->receiver = [_function](ARGS ... args)
			{
				_function(args...);
			};
			break;
		case Connection_Multithreaded:
			new_connector->receiver = [_function](ARGS ... args)
			{
				thread new_thread([_function, args ...]() {_function(args...); });
			};
			break;
		case Connection_Unary:
			new_connector->receiver = [&_event, &_receiver, _function](ARGS ... args)
			{
				_function(args...);
				_event.receivers_remove(&_receiver);
			};
			break;
		default:
			break;

		}
		arr_receivers.push_back(new_connector);
	}

	template <class OBJECT>
	void receivers_add(AFunction <void, ARGS ...> func, ConnectionType type = Connection_Immediate)
	{
		receivers_add(func.to_function(), type);
	}

	void receivers_remove(connector* _receiver)
	{
		for (int i = 0; i < arr_receivers.size(); i++)
			if (arr_receivers[i] == _receiver)
				arr_receivers.erase(arr_receivers.begin() += i);
	}

	vector <connector*> receivers()
	{
		return arr_receivers;
	}

	AEvent& waitForReceive(int duration_msec = DEFAULT_WAIT_DURATION, int frequency_msec = DEFAULT_WAIT_FREQUENCY)
	{
		fld_emited = false;
		while (!fld_emited)
		{
			if (frequency_msec)
				this_thread::sleep_for(chrono::milliseconds(frequency_msec));
		}
		return *this;
	}

    std::function <void(ARGS& ...)> receive;

	void private_is_Emited()
	{
		fld_emited = true;
	}

private:
	bool fld_emited = false;
	AIdentifier& id;
    std::function <void(ARGS ...)> fld_function;
	vector <connector*> arr_receivers;
};
