#pragma once
#include "asqlite_request.h"

#include <QVector>

using namespace std;


class ASQLiteRow
{
public:
	ASQLiteRow()
	{

	}

	ASQLiteRow& field_add(ASQLiteField _field)
	{
		arr_fields.push_back(_field);
		return *this;
	}

	void clear()
	{
		arr_fields.clear();
	}

	bool exist(sqlstring column_name) const
	{
		for (auto fld : arr_fields)
			if (fld.name == column_name)
				return true;
		return false;
	}

	const ASQLiteField field(sqlstring column_name) const
	{
		for (auto fld : arr_fields)
			if (fld.name == column_name)
					return fld;
		return ASQLiteField();
	}

	const astring to_string() const
	{
		astring result;
		for (auto _field : arr_fields)
		{
            result += astring(_field.data) + " ";
		}
		return result;
	}

private:
    QVector <ASQLiteField> arr_fields;
};


class ASQLiteReply
{
public:
	ASQLiteReply()
	{
		fld_idColumn = "";
	}

	ASQLiteReply(sqlstring _idColumn)
	{
		fld_idColumn = _idColumn;
	}

	ASQLiteReply& row_add(ASQLiteRow _row)
	{
		arr_rows.push_back(_row);
		return *this;
	}

	void clear()
	{
		arr_rows.clear();
	}

	ASQLiteReply& setIdColumn(sqlstring _column)
	{
		fld_idColumn = _column;
		return *this;
	}

	bool column_exist(sqlstring column_name) const
	{
		if (arr_rows.size() == 0)
			return false;
		if (!arr_rows[0].exist(column_name))
			return false;
		return true;
	}

	bool row_exist(sqlstring column_name, sqlstring _data) const
	{
		for (auto _row : arr_rows)
			if (_row.exist(column_name))
				if (_row.field(column_name).data == _data)
					return true;
		return false;
	}

	const ASQLiteRow row(sqlstring column_name, sqlstring _data) const
	{
		for (auto _row : arr_rows)
			if (_row.exist(column_name))
			{
				ASQLiteField _field = _row.field(column_name);
				if (_field.data == _data)
					return _row;
			}
		return ASQLiteRow();
	}

	const ASQLiteRow row(sqlstring _data) const
	{
        if(fld_idColumn.isEmpty())
			return ASQLiteRow();
		return row(fld_idColumn, _data);
	}

	const astring to_string() const
	{
		astring result;
		for (auto row : arr_rows)
		{
            result += row.to_string() + "\n";
		}
		return result;
	}

private:
	sqlstring fld_idColumn;
	vector <ASQLiteRow> arr_rows;
};
