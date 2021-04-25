#pragma once
#include "asqlite_reply.h"
#include "libs/windows/sqlite3.h"
#include "Engine/asoka.h"

using namespace std;


class ASQLiteDatabase
{
public:
	ASQLiteDatabase(sqlstring database_name)
	{
        DEBUG_LOG(astring("Соединение с базой данных: ") + database_name);
		fld_error.clear();
		obj_error_function = NULL;
        fld_opening_status = sqlite3_open(database_name.toStdString().c_str(), &obj_database);
		if (fld_opening_status)
            private_error("Не удалось открыть базу данных" + database_name);
        //ASQLiteDatabase& _database = *this;
		callback = [](void* data, int argc, char** argv, char** name) -> int
		{
			ASQLiteDatabase* _database = static_cast <ASQLiteDatabase*> (data);
			ASQLiteRow new_row;
			for (int i = 0; i < argc; i++)
			{
				ASQLiteField new_field;
				new_field.name = name[i];
				new_field.data = argv[i];
				new_row.field_add(new_field);
			}
			_database->private_reply_row_add(new_row);
			return 0;
		};
	}

	const ASQLiteReply& request(ASQLiteRequest _request)
	{
		//cout << endl << "SQL запрос: " << _request.to_string().to_std_string();
        DEBUG_LOG(astring("SQL запрос: ") + _request.to_astring());
		fld_error.clear();
		obj_reply.clear();
		fld_request_status = sqlite3_exec(obj_database, _request.to_char(), callback, this, &fld_request_error);
		if (fld_request_status != SQLITE_OK)
			private_error(Asoka::to_string(fld_request_error));
		return obj_reply;
	}

	void request_async(sqlstring _request)
	{

	}

	bool error()
	{
        return !fld_error.isEmpty();
	}

	astring lastError()
	{
		return fld_error;
	}

    ASQLiteDatabase& if_error(void (*_function)(astring) = NULL)
	{
		obj_error_function = _function;
		return *this;
	}

	void private_reply_row_add(ASQLiteRow _row)
	{
		obj_reply.row_add(_row);
	}

	int (*callback)(void*, int, char**, char**);

	AEvent <ASQLiteReply> reply;

private:
	void private_error(astring _error)
	{
        DEBUG_LOG(astring("SQL ошибка: ") + _error);
		fld_error = _error;
		if (obj_error_function != NULL)
			obj_error_function(fld_error);
	}

	ASQLiteReply				obj_reply;
	sqlite3*					obj_database;
	int							fld_opening_status;
	int							fld_request_status;
	char*						fld_request_error;
	astring						fld_error;
    void                        (*obj_error_function)(astring);
};


using ASqlDatabase	= ASQLiteDatabase;
using ASqlRequest	= ASQLiteRequest;
using ASqlReply		= ASQLiteReply;
using ASqlField		= ASQLiteField;


class Tester_ASQLite
{
public:
	Tester_ASQLite();

	void table_create();
	void table_insert();
	void table_select();
	void table_update();
	void table_remove();
	void table_drop();
	void table_output();
	void table_full();

private:
	sqlstring			table_name;

	ASQLiteDatabase*	database;
	ASqlRequest*		request;
};
