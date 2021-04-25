#pragma once
#include <iostream>
#include <time.h>

#include "DefaultTypes/astring.h"
#include "Engine/aobject.h"
#include "Engine/asoka.h"

using namespace std;


enum FormatTime {FreeTimeFormat, TextTimeFormat, HH_MM_SS, HH_MM};

enum FormatDate {FreeDataFormat, TextDataFormat, DD_MM_YY, DD_MM_YYYY, DD_MM};

enum FormatTimepoint { FreeTimepointFormat, TextTimepointFormat, HH_MM_DD_MM_YY, HH_MM_SS_DD_MM_YYYY, HH_MM_DD_MM };


class ATime
{
public:
				
    ATime()
    {
        set(0, 0, 0);
    }
  
    ATime(int _hours, int _minutes, int _seconds = 0)
    {
        set(_hours, _minutes, _seconds);
    }
    
    ATime(int _seconds)
    {
        set(_seconds);
    }

    void operator () (int _hours, int _minutes, int _seconds = 0)
    {
        set(_hours, _minutes, _seconds);
    }

    void operator () (int _seconds)
    {
        set(_seconds);
    }
  
    void set(int _hours, int _minutes, int _seconds = 0)
    {
        if(_hours >= 0 && _hours < 24)
            fld_hours = _hours;
        else
            fld_hours = 0;
      
								if(_minutes >= 0 && _minutes < 60)
								    fld_minutes = _minutes;
								else
								    fld_minutes = 0;
    
								if(_seconds >= 0 && _seconds < 60)
            fld_seconds = _seconds;
        else
            fld_seconds = 0;
    }
  
    void set(int seconds)
    {
        int total_seconds = seconds;
        fld_hours = total_seconds / 60 / 60;
        fld_minutes = (total_seconds / 60) % 60;
        fld_seconds = total_seconds % 60;
    }
    
    int hours()
    {
        return fld_hours;
    }
    
    int minutes()
    {
        return fld_minutes;
    }
    
    int seconds()
    {
        return fld_seconds;
    }
    
    astring to_astring(FormatTime format = FreeTimeFormat)
    {
        astring result;
        result += Asoka::to_string(fld_hours);
        result += ":" + Asoka::to_string(fld_minutes);
        if((fld_seconds != 0 && format == FreeTimeFormat) || format == HH_MM_SS)
            result += ":" + Asoka::to_string(fld_seconds);
        return result;
    }
    
    
    static ATime currentTime()
    {
        time_t _seconds = time(NULL);
								ATime timenow(_seconds % (60 * 60 * 24));
								return timenow;
    }
  
private:
  
    
    
    int fld_hours, fld_minutes, fld_seconds;
    
};
