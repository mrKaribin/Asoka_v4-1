#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <stdarg.h>
#include <cstdlib>
#include <mutex>
#include <QVector>

#include "DefaultTypes/astring.h"
#include "Engine/typedefs.h"
#include "Engine/templates.h"

#define DEFAULT_OBJECT_NAME "default"
#define DEFAULT_WAIT_FREQUENCY 100
#define DEFAULT_WAIT_DURATION 100

#define CLASS_NAME(class) \
    Asoka::to_string(typeid(class).name())

#define DEBUG_ON() Asoka::Testing::debug = true;

#define DEBUG_OFF() Asoka::Testing::debug = false;

#define DEBUG_SAVE() bool lastDebugStatus = Asoka::Testing::debug

#define DEBUG_PAUSE() \
	DEBUG_SAVE(); \
	if(Asoka::Testing::debug) \
		DEBUG_OFF(); \

#define DEBUG_RESTORE() \
	Asoka::Testing::debug = lastDebugStatus;

#define DEBUG_LOG(astring) \
    if(Asoka::Testing::debug) Asoka::output(astring);

using namespace std;

class AConsole;
class ACore;
class ATask;
class ASQLiteDatabase;


namespace Asoka
{
	enum OutputType { Output_Exact = 0, Output_Textual, Output_Literary, Output_Scientific};
	enum InputType { Input_Exact = 0, Input_Textual, Input_Audial };

	enum ClosingType { Closing_Default = 0, Closing_Fast,  Closing_Critical };

	namespace Testing
	{
		struct TestingError
		{
			wstring module = L"";
			wstring name = L"";
			wstring expexted = L"";
			wstring realy = L"";
			wstring type = L"";
		};

		extern bool						debug;
		extern time_t					time_begin;
		extern time_t					time_finish;
		extern vector <TestingError>	errors;

		extern void begin();

		extern void error(wstring module, wstring name, wstring expected, wstring realy);

		extern void error(wstring module, wstring name, wstring type = L"default");

		extern void finish();
	}

	namespace Core
	{
		extern Object <ACore> core;
		extern Object <AConsole> console;
	}

	namespace Log 
	{
		enum Type { Log_Debug = 0, Log_Info, Log_Warn, Log_Error };

		struct Page
		{
            astring name;
		};

		extern void				initialization();

        extern void				note(Page& _page, Type type, astring _message);
        extern inline void		debug(Page& _page, astring _message);
        extern inline void		info(Page& _page, astring _message);
        extern inline void		warn(Page& _page, astring _message);
        extern inline void		error(Page& _page, astring _message);
		
        extern Page&			page(astring page_name);

        extern Data <QVector <Page*>>           pages;
        extern const astring					pages_core_name;
        extern const astring					pages_service_name;
	}

	//------------------------------------------------------------------------------------------------------------------

	extern void initialization();

	extern void close(int code);

	extern void execute_gui();

	extern ASQLiteDatabase*		database;
	extern bool					thread_gui_run;
	extern thread::id			thread_gui_id;

	//------------------------------------------------------------------------------------------------------------------

	extern void wait(int milliseconds);

    extern void output(const astring message, OutputType type = Output_Exact);
	extern wostream& output(OutputType type = Output_Exact);

    extern astring input(InputType type = Input_Exact);

	extern astring to_string(const char* _str);
	extern astring to_string(string str);
	extern astring to_string(int value);
	extern astring to_string(float value);
	extern astring to_string(bool value);
    extern string to_std_string(const astring str);

    extern const char* to_char(const int value);

    extern int to_int(const astring str);
    extern int to_int(const bit8* data);

    extern bool to_bool(const bit8* data);

	extern int random(int from = 0, int to = RAND_MAX - 1);
	extern bool random_chance(float _chance);
	extern bool random_logic();
	extern bit8 random_byte();
	extern wchar random_wchar();
    extern astring random_astring(int lenth = 10);
}
