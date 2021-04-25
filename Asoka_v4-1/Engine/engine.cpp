#ifdef _WIN32
#include <Windows.h>
#endif
#include "../Engine/asoka.h"
//#include "../Engine/Console/asoka_console.h"
#include "../Engine/aidentifier.h"
#include "../Engine/athread.h"
#include "../Instruments/SQL/SQLITE/asqlite.h"
#include "../DefaultTypes/atime.h"

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

using namespace std;


namespace Asoka
{

	namespace Testing
	{
		bool debug = false;
		time_t time_begin;
		time_t time_finish;
		vector <TestingError> errors;

		void begin()
		{
			errors.clear();
			time_finish = 0;
			time_begin = time(NULL);
		}

		void error(wstring module, wstring name, wstring expected, wstring realy)
		{
			TestingError new_error;
			new_error.module = module;
			new_error.name = name;
			new_error.expexted = expected;
			new_error.realy = realy;
			errors.push_back(new_error);
		}

		void error(wstring module, wstring name, wstring type)
		{
			TestingError new_error;
			new_error.module = module;
			new_error.name = name;
			new_error.type = type;
		}

		void finish()
		{
			time_finish = time(NULL);
		}
	}

	//------------------------------------------------------------------------------------------------------------------

	namespace Core
	{
		Object <ACore> core;
		Object <AConsole> console;
	}

	//------------------------------------------------------------------------------------------------------------------

	namespace Log
	{
		void initialization()
		{
			database->request(ASqlRequest().CREATE_TABLE("log", 5,
				ASQLiteColumn("id", "INTEGER").SET_PRIMARY_KEY(),
				ASQLiteColumn("page", "CHAR(50)").SET_NOT_NULL().SET_DEFAULT("'" + pages_service_name + "'"),
				ASQLiteColumn("type", "INTEGER").SET_NOT_NULL().SET_DEFAULT("1"),
				ASQLiteColumn("message", "TEXT"),
				ASQLiteColumn("date", "TIMEPOINT").SET_NOT_NULL().SET_DEFAULT("'00.00.00T00:00'")));
		}

        void note(Page& _page, Type _type, astring _message)
		{
			database->request(ASqlRequest().INSERT("log", 4, 
                ASQLiteField("page", "'" + _page.name + "'"),
                ASQLiteField("type", astring::number(_type)),
				ASQLiteField("message", "'" + _message + "'"),
				ASQLiteField("date", "'00.00.00T00:00'")));
		}

        inline void debug(Page& _page, astring _message)
		{
			note(_page, Log_Debug, _message);
		}

        inline void info(Page& _page, astring _message)
		{
			note(_page, Log_Info, _message);
		}

        inline void warn(Page& _page, astring _message)
		{
			note(_page, Log_Warn, _message);
		}

        inline void error(Page& _page, astring _message)
		{
			note(_page, Log_Error, _message);
		}

        Page& page(astring page_name)
		{
			pages.lock();
			for (auto _page : pages())
			{
				if (_page->name == page_name)
				{
					pages.unlock();
					return *_page;
				}
			}

			Page* _page = new Page;
			_page->name = page_name;
			pages().push_back(_page);
			pages.unlock();
			return *_page;
		}

        Data <QVector<Page*>> pages(new QVector <Page*>);
        const astring pages_core_name = "AsokaCore";
        const astring pages_service_name = "Service";
	}

	//------------------------------------------------------------------------------------------------------------------

	void initialization()
	{
		//Asoka---------------------------------------------------------------------------------------------------------

#ifdef _WIN32
		setlocale(LC_ALL, "Russian");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
#endif
		srand(time(0));
		database = new ASqlDatabase("AsokaEngineDatabase.db"); 
        database->if_error([](astring error) {Asoka::output("\nОшибка базы данных SQL: " + error); });
		Log::initialization();

		//AsokaCore-----------------------------------------------------------------------------------------------------
		ACore::initialize();
		Core::core = new ACore();
	}

	void close(int code)
	{
		ACore::close();
		if (Core::core.exist())
			Core::core().~ACore();
		exit(code);
	}

	void execute_gui()
	{
		while (true)
		{
			if (thread_gui_run)
			{
                Asoka::output() << "Поток: " << this_thread::get_id();
				Asoka::Core::core().thread_free(Task_Interface).run(true);
				thread_gui_run = false;
			}
		}
	}

	ASqlDatabase* database;
	bool thread_gui_run = false;
	thread::id thread_gui_id = this_thread::get_id();

	//------------------------------------------------------------------------------------------------------------------

	void output(const astring message, OutputType type)
	{
        std::cout << astring("\n" + message).toStdString();
    }

	wostream& output(OutputType type)
	{
		return wcout;
	}

    astring input(InputType type)
	{
        string _str;
        cin >> _str;
        return _str;
    }

	void wait(int milliseconds)
	{
		this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}

//-----------------------------------------------------------------------------------------------------------------------------

	astring to_string(const char* _str)
    {
        return astring(_str);
	}

	astring to_string(int value)
    {
        astring::number(value);
	}

	astring to_string(float value)
    {
        astring::number(value);
	}

	astring to_string(bool value)
	{
		if (value)
            return astring("true");
		else
            return astring("false");
	}

	astring to_string(string str)
	{
        return astring(str);
	}

	string to_std_string(astring str)
	{
        return str.toStdString();
    }

	const char* to_char(const int value)
	{
		char res[10] = "";
#ifdef _WIN32
		_itoa_s(value, res, 5, 10);
		return res;
#endif
#ifdef ANDROID_API_LEVEL_H
		return astring(res);
#endif
    }

    int to_int(const bit8* data)
	{
		int result;
		memcpy(&result, data, sizeof(int));
		return result;
	}

    int to_int(const astring str)
	{
        return str.toInt();
	}

    bool to_bool(const bit8* data)
	{
		if (*data != 0)
			return true;
		else
			return false;
	}

	int random(int from, int to)
	{
		return rand() % (to + 1 - from) + from;
	}

	bool random_chance(float _chance)
	{
		if (random(0, 10000) <= _chance * 100)
			return true;
		else
			return false;
	}

	bool random_logic()
	{
		return (bool)random(0, 1);
	}

	bit8 random_byte()
	{
		return (bit8)random(0, 255);
	}

	wchar random_wchar()
	{
		return (wchar)random(0, 65535);
	}

	astring random_string(int lenth)
	{
		astring result;
		for (int i = 0; i < lenth; i++)
			result += random_wchar();
		return result;
    }
}


//-----------------------------------------------------------------------------------------------------------------------------------


astring::astring(const string str) : QString(Asoka::to_string(str)) {}

const astring astring::operator + (const char str[])
{
    astring buffer = *this;
    buffer.append(str);
	return buffer;
}

const astring astring::operator + (const string str)
{
    astring buffer = *this;
    buffer.append(astring(str));
	return buffer;
}

const astring astring::operator + (const astring str)
{
    astring buffer = *this;
    buffer.append(str);
    return buffer;
}

const astring operator + (const char str1[], astring str2)
{
    return astring(str1) + astring(str2);
}

//-----------------------------------------------------------------------------------------------------------------------

ATask::ATask(astring _name, TaskType type) : fld_id(ACore::identifier_create(this, _name))
{
	std_thread = NULL;
	fld_type = type;
	fld_status = Task_Queued;
	fld_time_start = 0;
	fld_time_finish = 0;
	fld_duration_last = 0;
}

void ATask::proceed(AThread& _thread)
{
    if (!_thread.stoped())
        _thread.run(true);
}

astring ATask::taskLog(ATask& _task, AThread& _thread)
{
    return "Running task <" + _task.id().name() + "> in thread <" + _thread.id().name() + ">";
}

Asoka::Log::Page& ATask::fld_page = Asoka::Log::page("Задачи");
Data <map <string, long long*>> ATask::durations = new map <string, long long*>;

//-----------------------------------------------------------------------------------------------------------------------

AThread::AThread(astring _name) : fld_id(ACore::identifier_create(this))
{

}
