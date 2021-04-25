#pragma once
#include <QString>

using namespace std;

//using astring = basic_string <wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;

class astring : public QString
{
public:
    astring() : QString() {}

    astring(const QString str) : QString(str) {}

    astring(const astring& str) : QString(str) {}

    astring(const string str);

    astring(const char str[]) : QString(str) {}

	const astring& operator = (const astring& str)
	{
        QString::operator=(str);
		return *this;
	}

    const astring operator + (const string str);

    const astring operator + (const astring str);

    const astring operator + (const char str[]);

    const char* to_chars()
    {
        return toStdString().c_str();
    }
};
