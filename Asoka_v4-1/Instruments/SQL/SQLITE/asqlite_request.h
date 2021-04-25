#pragma once
#include "DefaultTypes/aevent.h"

using namespace std;

using sqlstring = astring;


struct ASQLiteColumn
{
	ASQLiteColumn(sqlstring _name, sqlstring _type)
	{
		name = _name;
		type = _type;
	}

	ASQLiteColumn& SET_PRIMARY_KEY(bool _PRIMARY_KEY = true)
	{
		PRIMARY_KEY = _PRIMARY_KEY;
		return *this;
	}

	ASQLiteColumn& SET_FOREIGN_KEY(sqlstring _FOREIGN_KEY_TABLE = "", sqlstring _FOREIGN_KEY_FIELD = "")
	{
        if (!_FOREIGN_KEY_TABLE.isEmpty())
		{
			FOREIGN_KEY = true;
			FOREIGN_KEY_TABLE = _FOREIGN_KEY_TABLE;
			FOREIGN_KEY_FIELD = _FOREIGN_KEY_FIELD;
		}
		else
		{
			FOREIGN_KEY = false;
			FOREIGN_KEY_TABLE = "";
			FOREIGN_KEY_FIELD = "";
		}
		return *this;
	}

	ASQLiteColumn& SET_UNIQUE(bool _UNIQUE = true)
	{
		UNIQUE = _UNIQUE;
		return *this;
	}

	ASQLiteColumn& SET_NOT_NULL(bool _NOT_NULL = true)
	{
		NOT_NULL = _NOT_NULL;
		return *this;
	}

	ASQLiteColumn& SET_DEFAULT(sqlstring _DEFAULT_VALUE)
	{
        if (!_DEFAULT_VALUE.isEmpty())
		{
			DEFAULT = true;
			DEFAULT_VALUE = _DEFAULT_VALUE;
		}
		return *this;
	}

	sqlstring name;
	sqlstring type;
	bool PRIMARY_KEY = false;
	bool NOT_NULL = false;
	bool UNIQUE = false;
	bool FOREIGN_KEY = false;
	sqlstring FOREIGN_KEY_TABLE = "";
	sqlstring FOREIGN_KEY_FIELD = "";
	bool DEFAULT = false;
	sqlstring DEFAULT_VALUE = "";
};


struct ASQLiteField
{
	ASQLiteField() {}

	ASQLiteField(sqlstring _name, sqlstring _data)
	{
		name = _name;
		data = _data;
	}

	sqlstring name;
	sqlstring data;
};


class ASQLiteRequest
{
public:
	ASQLiteRequest();
	ASQLiteRequest(sqlstring _request);

	ASQLiteRequest& operator == (sqlstring _request);
	ASQLiteRequest& operator () (sqlstring _request);

	ASQLiteRequest& set(sqlstring _request);

	ASQLiteRequest& WHERE(sqlstring where = "");
	ASQLiteRequest& ORDER(sqlstring order = "");
	ASQLiteRequest& LIMIT(sqlstring limit = "");
	ASQLiteRequest& CREATE_TABLE(sqlstring table_name, int count, ...);
	ASQLiteRequest& DROP_TABLE(sqlstring table_name);
	ASQLiteRequest& INSERT(sqlstring table, int count, ...);
	ASQLiteRequest& SELECT(sqlstring table, sqlstring values = "");
	ASQLiteRequest& UPDATE(sqlstring table, int count, ...);
	ASQLiteRequest& REMOVE(sqlstring _table); 

	const char* to_char();
    astring to_astring();

private:
	sqlstring fld_request;
};
