#pragma once
#include "Engine/athread.h"


template <class ... ARGS>
class AEvent;


class ACore
{
public:
	static void initialize();

	static void close(Asoka::ClosingType _type = Asoka::Closing_Default);

    static AIdentifier& identifier_create(void* _object, astring _name = DEFAULT_OBJECT_NAME)
	{
		AIdentifier* new_id;
		bool need_reservation = false;
		arr_identifiers.lock();
		if (!arr_identifiers().empty())
		{
            new_id = new AIdentifier(_object, arr_identifiers()[0], prt_identifier_name_check(_name));
			arr_identifiers().erase(arr_identifiers().begin());
		}
		else
		{
			new_id = new AIdentifier(_object, prt_identifier_create(), prt_identifier_name_check(_name));
			need_reservation = true;
		}
		arr_identifiers.unlock();
		if(need_reservation)
			identifier_reservation(fld_identifiers_reserve_size());
		identifiers.get().push_back(new_id);
		identifiers.unlock();
		return *new_id;
	}

	void identifier_remove(AIdentifier& _id)
	{

	}

	static void identifier_reservation(int count)
	{
		if (Asoka::Core::core.exist())
		{
			prt_identifier_reservating(1);
            //void (*func)(int) = &prt_identifier_reservating;
            std::function <int(int)> func = &prt_identifier_reservating;
            //thread_free().run(&prt_identifier_reservating, count, Task_Service, DEFAULT_OBJECT_NAME);
            ATask* task = new ATask();
            task->initialize(func, count);
		}
	}

	static AThread& thread_free(TaskType type = Task_Service)
	{
		if (threads_system().empty())
			return thread_custom();

		if (type == Task_Interface)
			return *threads_system()[0];

		threads_system.lock();
		long long minimum = threads_system()[0]->duration_total();
		AThread* result = threads_system()[0];
		for (auto athread : threads_system())
		{
			if (athread->duration_total() < minimum)
				result = athread;
		}
		threads_system.unlock();
		return *result;
	}

	static AThread& thread_custom(astring thread_name = DEFAULT_OBJECT_NAME)
	{
		if (threads_custom().empty())
			return *new AThread(thread_name);
		threads_custom.lock();
		AThread* result = NULL;
		for (auto athread : threads_custom())
			if (athread->id().name() == thread_name)
				result = athread;
		if (result == NULL)
			result = new AThread(thread_name);
		return *result;
	}

	static AEvent <Asoka::ClosingType>		closing;

    static Data <QVector <AIdentifier*>>		identifiers;
    static Data <QVector <AThread*>>			threads_system;
    static Data <QVector <AThread*>>			threads_custom;
	static const isize						threads_system_count;

private:
	static astring prt_identifier_name_check(astring _name)
	{
		if (_name == DEFAULT_OBJECT_NAME)
			return _name;
		identifiers.lock();
		for (auto id : identifiers())
			if (id->name() == _name)
			{
                int index = _name.lastIndexOf('#');
				if (index != -1)
				{
					int number = Asoka::to_int(_name.mid(index, _name.size() - index)) + 1;
					return prt_identifier_name_check(_name.mid(0, index - 1) + Asoka::to_string(number));
				}
				else
                    return prt_identifier_name_check(_name + "#" + Asoka::to_string(1));
			}
		identifiers.unlock();
		return _name;
	}

    static int prt_identifier_reservating(int count)
	{
		for (int i = 0; i < count; i++)
		{
			arr_identifiers.get().push_back(prt_identifier_create());
			arr_identifiers.unlock();
		}
        return 0;
	}

	static identifier prt_identifier_create()
	{
		for(int size = 1; true; size++)
		{
			identifier new_id;
			for (int i = 0; i < size; i++)
			{
				char new_value = 0;
				new_id.push_back(new_value);
				for (bit8 value = 0; value < 255; value++)
				{
					new_id[i] = value;
					if (!prt_identifier_find(new_id))
						return new_id;
				}
			}
		}
	}

	static inline bool prt_identifier_find(identifier _id)
	{
		bool ok = false;
		identifiers.lock();
		for (auto id : identifiers())
			if (*id == _id)
			{
				ok = true;
				break;
			}
		identifiers.unlock();
		return false;
	}

    static Data <QVector <identifier>>	arr_identifiers;
	static Data <int>					fld_identifiers_reserve_size;
};
