#include "Instruments/SQL/SQLITE/asqlite.h"
//#include "Engine/asoka.h"


//------------------------------------------------------------------------------------------------------------------

ASQLiteRequest::ASQLiteRequest()
{
	fld_request = "";
}

ASQLiteRequest::ASQLiteRequest(sqlstring _request)
{
	set(_request);
}

ASQLiteRequest& ASQLiteRequest::operator == (sqlstring _request)
{
	return set(_request);
}

ASQLiteRequest& ASQLiteRequest::operator () (sqlstring _request)
{
	return set(_request);
}

ASQLiteRequest& ASQLiteRequest::set(sqlstring _request)
{
	fld_request = _request;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::WHERE(sqlstring where)
{
    if (!where.isEmpty())
		fld_request += " WHERE " + where;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::ORDER(sqlstring order)
{
    if (!order.isEmpty())
		fld_request += " ORDER BY " + order;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::LIMIT(sqlstring limit)
{
    if (!limit.isEmpty())
		fld_request += " LIMIT " + limit;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::CREATE_TABLE(sqlstring table_name, int count, ...)
{
	sqlstring result = "CREATE TABLE IF NOT EXISTS " + table_name + " ("; //[] 
	va_list arg;
	va_start(arg, count);
	for (int i = 0; i < count; i++)
	{
        void* _column = va_arg(arg, void*);
        ASQLiteColumn column = *static_cast<ASQLiteColumn*>(_column);
		result += column.name + " ";
		result += column.type + " ";
		if (column.PRIMARY_KEY)
			result += "PRIMARY KEY ";
		if (column.FOREIGN_KEY)
			result += "REFERENCES " + column.FOREIGN_KEY_TABLE + " (" + column.FOREIGN_KEY_FIELD + ") ";
		if (column.UNIQUE)
			result += "UNIQUE ";
		if (column.NOT_NULL)
			result += "NOT NULL ";
		if (column.DEFAULT)
			result += "DEFAULT (" + column.DEFAULT_VALUE + ") ";
		if (i < count - 1)
			result += ", ";
	}
	result += ");";
	fld_request = result;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::DROP_TABLE(sqlstring table_name)
{
	fld_request = "DROP TABLE IF EXISTS " + table_name + " ;";
	return *this;
}

ASQLiteRequest& ASQLiteRequest::INSERT(sqlstring table, int count, ...)
{
	sqlstring header = "INSERT INTO " + table + " (";
	sqlstring body = " VALUES (";
	va_list arg;
	va_start(arg, count);
	for (int i = 0; i < count; i++)
	{
        void* _current = va_arg(arg, void*);
        ASQLiteField current = *static_cast<ASQLiteField*>(_current);
		header += current.name;
		body += current.data;
		if (i < count - 1)
		{
			header += ", ";
			body += ", ";
		}
	}
	va_end(arg);
	header += ")";
	body += ");";
	fld_request = header + body;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::SELECT(sqlstring table, sqlstring values)
{
	fld_request.clear();
    if (values.isEmpty())
		fld_request += "SELECT * FROM " + table;
	else
		fld_request += "SELECT " + values + " FROM " + table;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::UPDATE(sqlstring table, int count, ...)
{
	sqlstring result = "UPDATE " + table + " SET ";
	va_list arg;
	va_start(arg, count);
	for (int i = 0; i < count; i++)
	{
        void* _current = va_arg(arg, void*);
        ASQLiteField current = *static_cast<ASQLiteField*>(_current);
		result += current.name + " = " + current.data;
		if (i != count - 1)
			result += ", ";
	}
	va_end(arg);
	fld_request = result;
	return *this;
}

ASQLiteRequest& ASQLiteRequest::REMOVE(sqlstring _table)
{
	fld_request = "DELETE FROM " + _table;
	return *this;
}

const char* ASQLiteRequest::to_char()
{
    return fld_request.toStdString().c_str();
}

astring ASQLiteRequest::to_astring()
{
	return fld_request;
}

//------------------------------------------------------------------------------------------------------------------

Tester_ASQLite::Tester_ASQLite()
{
	DEBUG_PAUSE();
	database = new ASQLiteDatabase("database.db");
	if (!Asoka::Testing::debug)
        database->if_error([](astring error) {Asoka::output("\nSQL Database error: " + error); });
	request = new ASQLiteRequest();
	table_name = "new_table_1";
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_create()
{
	DEBUG_PAUSE();
    Asoka::output("Создаю таблицу " + astring(table_name));
	request->CREATE_TABLE(table_name, 5,
		ASQLiteColumn("id", "integer").SET_PRIMARY_KEY(),
		ASQLiteColumn("number", "integer").SET_NOT_NULL().SET_DEFAULT("-1"),
		ASQLiteColumn("status", "boolean").SET_NOT_NULL().SET_DEFAULT("0"),
		ASQLiteColumn("time", "time").SET_NOT_NULL().SET_DEFAULT("'00:00'"),
		ASQLiteColumn("body", "text").SET_NOT_NULL().SET_DEFAULT("'empty'"));
	database->request(*request);
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_insert()
{
	DEBUG_PAUSE();
	using namespace Asoka;
    Asoka::output("Заполняю таблицу данными: ");
	for (int i = 0; i < random(10, 30); i++)
	{
		database->request(request->INSERT(table_name, 4,
            ASQLiteField("number", Asoka::to_string(random(0, 99)).toStdString()),
            ASQLiteField("status", Asoka::to_string(random_logic()).toStdString()),
            ASQLiteField("time", "'" + Asoka::to_string(random(0, 23)).toStdString() + ":" + Asoka::to_string(random(0, 59)).toStdString() + "'"),
            ASQLiteField("body", "'teststring" + Asoka::to_string(i + 1).toStdString() + "'")));
	}
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_select()
{
	DEBUG_PAUSE();
	ASqlReply reply = database->request(request->SELECT(table_name, "id, number, time").WHERE("number < 30").ORDER("number"));
    Asoka::output("Выполняю: " + request->to_astring());
	Asoka::output(reply.to_string());
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_update()
{
	DEBUG_PAUSE();
	ASqlReply reply = database->request(request->UPDATE(table_name, 2, ASqlField("body", "'updated_string'"), ASqlField("time", "'00:00'")).WHERE("number > 70"));
    Asoka::output("Выполняю: " + request->to_astring());
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_remove()
{
	DEBUG_PAUSE();
	ASqlReply reply = database->request(request->REMOVE(table_name).WHERE("body != 'updated_string'"));
    Asoka::output("Выполняю: " + request->to_astring());
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_drop()
{
	DEBUG_PAUSE();
    Asoka::output("Удаляю таблицу " + astring(table_name));
	database->request(request->DROP_TABLE(table_name));
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_output()
{
	DEBUG_PAUSE();
	ASqlReply reply = database->request(request->SELECT(table_name));
	Asoka::output(reply.setIdColumn("id").to_string());
	DEBUG_RESTORE();
}

void Tester_ASQLite::table_full()
{
	table_create();
	table_insert();
	table_output();
	table_select();
	table_update();
	table_output();
	table_remove();
	table_output();
	table_drop();
}
