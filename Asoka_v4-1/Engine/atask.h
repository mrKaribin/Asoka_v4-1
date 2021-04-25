#pragma once
#include <thread>
#include <mutex>
#include <chrono>
#include <map>

#include "aidentifier.h"

using namespace std;

enum TaskStatus { Task_Queued, Task_Running, Task_Finished };
enum TaskType { Task_Interface, Task_Service, Task_Logic, Task_Long };

class AThread;


class ATask
{
public:
    ATask(astring _name = DEFAULT_OBJECT_NAME, TaskType type = Task_Service);

    template <class OBJECT, class TYPE, class ... ARGS>
    void initialize(AMethod <OBJECT, TYPE, ARGS...> _method, ARGS ... args)
    {
        access.lock();
        ATask& _task = *this;
        OBJECT& _object = *_method.object();
        std::function <TYPE(OBJECT&, ARGS...)> _function = _method.to_function();
        fld_duration_last = duration_find(CLASS_NAME(_function).toStdString());
        //DEBUG_LOG(L"Длительность операции: " + Asoka::to_string((int)*fld_duration_last));
        //DEBUG_LOG(L"Размер статического словаря durations: " + Asoka::to_string((int)durations().size()));

        mth_start = [&_task, &_object, _function, args...](AThread& _thread) mutable
        {
            _task.std_thread = new thread([&_task, &_thread, &_object, _function, args...]() mutable
            {
                _task.status_set(Task_Running);
                Asoka::Log::debug(fld_page, ATask::taskLog(_task, _thread));
                _function(_object, args...);
                _task.status_set(Task_Finished);
                ATask::proceed(_thread);
            });
        };

        start = [&_task, &_object, _function, args...](AThread& _thread) mutable
        {
            _task.status_set(Task_Running);
            Asoka::Log::debug(fld_page, ATask::taskLog(_task, _thread));
            _function(_object, args...);
            _task.status_set(Task_Finished);
            ATask::proceed(_thread);
        };
        access.unlock();
    }

    template <class OBJECT, class TYPE, class ... ARGS>
    void initialize(OBJECT& _object, TYPE (OBJECT::*_function)(ARGS...), ARGS ... args)
    {
        AMethod <OBJECT, TYPE, ARGS ...> _method(&_object, _function);
        initialize(_method, args...);
    }

    template <class TYPE, class ... ARGS>
    void initialize(AFunction <TYPE, ARGS...> _function, ARGS ... args)
    {
        std::function <TYPE(ARGS...)> __function = _function.to_function();
        initialize(__function, args ...);
    }

    template <class TYPE, class ... ARGS>
    void initialize(std::function <TYPE(ARGS ...)> _function, ARGS ... args)
    {
        access.lock();
        ATask& _task = *this;
        fld_duration_last = duration_find(CLASS_NAME(_function).toStdString());
        //DEBUG_LOG(L"Длительность операции: " + Asoka::to_string((int)*fld_duration_last));
        //DEBUG_LOG(L"Размер статического словаря durations: " + Asoka::to_string((int)durations().size()));

        mth_start = [&_task, _function, args...](AThread& _thread) mutable
        {
            _task.std_thread = new thread([&_task, &_thread, _function, args...]() mutable
            {
                _task.status_set(Task_Running);
                //Asoka::output() << endl << L"Запустилась задача " << _task.id().name() << L" в потоке: " << this_thread::get_id();
                _function(args...);
                _task.status_set(Task_Finished);
                ATask::proceed(_thread);
            });
        };

        start = [&_task, _function, args...](AThread& _thread) mutable
        {
            _task.status_set(Task_Running);
            //Asoka::output() << endl << L"Запустилась задача " << _task.id().name() << L" в потоке: " << this_thread::get_id();
            _function(args...);
            _task.status_set(Task_Finished);
            ATask::proceed(_thread);
        };
        access.unlock();
    }

    static void proceed(AThread& _thread);

    static astring taskLog(ATask& _task, AThread& _thread);

    TaskType type()
    {
        access.lock();
        TaskType result = fld_type;
        access.unlock();
        return result;
    }

    TaskStatus status()
    {
        access.lock();
        TaskStatus result = fld_status;
        access.unlock();
        return result;
    }

    const AIdentifier& id() const
    {
        return fld_id;
    }

    long long duration_last()
    {
        return *fld_duration_last;
    }

    long long duration()
    {
        using namespace std::chrono;
        if (fld_time_start == 0)
            return fld_time_start;
        if (fld_time_finish == 0)
            return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - fld_time_start;
        else
            return 0;
    }

    void status_set(TaskStatus _status)
    {
        using namespace std::chrono;
        access.lock();
        fld_status = _status;
        if (_status == Task_Running)
            fld_time_start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        else if (_status == Task_Finished)
        {
            fld_time_finish = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            *fld_duration_last = fld_time_finish - fld_time_start;
        }
        access.unlock();
    }

    static long long* duration_find(string _typename)
    {
        durations.lock();
        for (auto duration : durations())
        {
            if (duration.first == _typename)
            {
                durations.unlock();
                return duration.second;
            }
        }
        durations.unlock();
        long long* new_duration = new long long(100);
        durations().insert(make_pair(_typename, new_duration));
        return new_duration;
    }

    std::function <void(AThread&)> start;
    std::function <void(AThread&)> mth_start;
    thread* std_thread;
    static Data <map <string, long long*>> durations;

    friend thread;

private:
    static Asoka::Log::Page& fld_page;
    AIdentifier&	fld_id;
    TaskStatus		fld_status;
    TaskType		fld_type;
    mutex access;
    long long	fld_time_start;
    long long	fld_time_finish;
    long long*	fld_duration_last;
};
