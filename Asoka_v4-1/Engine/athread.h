#pragma once
#include "atask.h"

using namespace std;


class AThread
{
public:
    AThread(astring _name = DEFAULT_OBJECT_NAME);

    ~AThread()
    {

    }

    void run(bool inThread = false)
    {
        access.lock();
        fld_stoped = false;
        while (!arr_tasks.empty())
        {
            if (arr_tasks[0]->status() == Task_Running)
                break;
            else
            {
                if (arr_tasks[0]->status() == Task_Finished)
                {
                    arr_tasks.erase(arr_tasks.begin());
                    fld_currentTask = NULL;
                    continue;
                }
                else if (arr_tasks[0]->status() == Task_Queued)
                {
                    if (arr_tasks[0]->type() == Task_Interface)
                    {
                        if (this_thread::get_id() != Asoka::thread_gui_id)
                        {
                            Asoka::thread_gui_run = true;
                            access.unlock();
                            return;
                        }
                        else
                            inThread = true;
                    }
                    fld_currentTask = arr_tasks[0];
                    if (inThread)
                    {
                        access.unlock();
                        fld_currentTask->start(*this);
                        return;
                    }
                    else
                        fld_currentTask->mth_start(*this);
                    break;
                }
            }
        }
        access.unlock();
    }

    template <class OBJECT, class TYPE, class ... ARGS>
    void run(AMethod <OBJECT, TYPE, ARGS...> _method, ARGS ... args, TaskType type = Task_Service, astring name = DEFAULT_OBJECT_NAME)
    {
        fld_stoped = false;
        addTask(_method, args..., type, name);
        if (fld_currentTask == NULL)
            run();
    }

    template <class OBJECT, class TYPE, class ... ARGS>
    void run(OBJECT& _object, TYPE (OBJECT::*_function)(ARGS ...), ARGS ... args, TaskType type = Task_Service, astring name = DEFAULT_OBJECT_NAME)
    {
        fld_stoped = false;
        addTask(_object, _function, args..., type, name);
        if (fld_currentTask == NULL)
            run();
    }

    template <class OBJECT, class TYPE, class ... ARGS>
    void run(OBJECT& _object, TYPE(OBJECT::* _function)(), TaskType type = Task_Service, astring name = DEFAULT_OBJECT_NAME)
    {
        fld_stoped = false;
        addTask(_object, _function, type, name);
        if (fld_currentTask == NULL)
            run();
    }

    template <class TYPE, class ... ARGS>
    void run(AFunction <TYPE, ARGS...> _function, ARGS ... args, TaskType type = Task_Service, astring name = DEFAULT_OBJECT_NAME)
    {
        std::function <TYPE(ARGS...)> __function = _function.to_function();
        run(__function, _function, args ..., type, name);
    }

    template <class TYPE, class ... ARGS>
    void run(std::function <TYPE(ARGS...)> _function, ARGS ... args, TaskType type = Task_Service, astring name = DEFAULT_OBJECT_NAME)
    {
        fld_stoped = false;
        addTask(_function, args..., type, name);
        if (fld_currentTask == NULL)
            run();
    }

    template <class OBJECT, class TYPE, class ... ARGS>
    void addTask(AMethod <OBJECT, TYPE, ARGS...> _method, ARGS ... args, TaskType type = Task_Service, astring _name = DEFAULT_OBJECT_NAME)
    {
        ATask* new_ATask = new ATask(_name, type);
        new_ATask->initialize(_method, args ...);
        arr_tasks.push_back(new_ATask);
    }

    template <class OBJECT, class TYPE, class ... ARGS>
    void addTask(OBJECT& _object, TYPE (OBJECT::* _function)(ARGS ...), ARGS ... args, TaskType type = Task_Service, astring _name = DEFAULT_OBJECT_NAME)
    {
        ATask* new_ATask = new ATask(_name, type);
        new_ATask->initialize(_object, _function, args ...);
        arr_tasks.push_back(new_ATask);
    }

    template <class OBJECT, class TYPE>
    void addTask(OBJECT& _object, TYPE(OBJECT::* _function)(), TaskType type = Task_Service, astring _name = DEFAULT_OBJECT_NAME)
    {
        ATask* new_ATask = new ATask(_name, type);
        new_ATask->initialize(_object, _function);
        arr_tasks.push_back(new_ATask);
    }

    template <class TYPE, class ... ARGS>
    void addTask(AFunction <TYPE, ARGS...> _function, ARGS ... args, TaskType type = Task_Service, astring _name = DEFAULT_OBJECT_NAME)
    {
        ATask* new_ATask = new ATask(_name, type);
        new_ATask->initialize(_function, args ...);
        arr_tasks.push_back(new_ATask);
    }

    template <class TYPE, class ... ARGS>
    void addTask(TYPE(*_function)(ARGS ...), ARGS ... args, TaskType type = Task_Service, astring _name = DEFAULT_OBJECT_NAME)
    {
        ATask* new_ATask = new ATask(_name, type);
        new_ATask->initialize(_function, args ...);
        arr_tasks.push_back(new_ATask);
    }

    void stop()
    {
        access.lock();
        fld_stoped = true;
        access.unlock();
    }

    const bool stoped() const
    {
        return fld_stoped;
    }

    const AIdentifier& id()
    {
        return fld_id;
    }

    isize size()
    {
        return arr_tasks.size();
    }

    long long duration_total()
    {
        long long total = 0;
        for (auto task : arr_tasks)
            if(task->status() != Task_Finished)
                total += task->duration_last();
        return total;
    }

    ATask& tasks_current()
    {
        return *fld_currentTask;
    }

    const AThread& waitForFinished(int milliseconds = -1, int frequency = 100)
    {
        while (!arr_tasks.empty())
        {
            if(frequency)
                this_thread::sleep_for(chrono::milliseconds(frequency));
        }
        return *this;
    }

    const AThread& waitForStoped(int milliseconds = -1, int frequency = 100)
    {
        while (!fld_stoped)
        {
            if (frequency)
                this_thread::sleep_for(chrono::milliseconds(frequency));
        }
        return *this;
    }

    mutex access;

private:
    AIdentifier&	fld_id;
    bool			fld_stoped			= false;
    vector <ATask*>	arr_tasks;
    ATask*			fld_currentTask		= NULL;
};


namespace Asoka
{
    template <class ... ARGS>
    extern void execute_service(void(*_function)(ARGS ...), ARGS ... args)
    {
        Asoka::Core::core().thread_free(Task_Service).run(_function, args ...);
    }

    template <class OBJECT, class ... ARGS>
    extern void execute_service(OBJECT& _object, void(OBJECT::* _function)(ARGS ...), ARGS ... args)
    {
        Asoka::Core::core().thread_free(Task_Service).run(_object, _function, args ...);
    }
}
