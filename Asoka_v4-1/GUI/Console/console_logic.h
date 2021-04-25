#ifndef CONSOLE_LOGIC_H
#define CONSOLE_LOGIC_H

#include "Engine/aobject.h"

#include <QObject>


class ConsoleLogic : public QObject, AObject
{
    Q_OBJECT
public:

private:

public slots:
    void runCommand(astring command)
    {
        QStringList words = command.split(" ");
        if(!words.isEmpty() && !words[0].isEmpty())
        {
            if(words[0] == "listen")
            {

            }
            else if(words[0] == "menu")
            {

            }
            else if(words[0] == "files")
            {

            }
            else if(words[0] == "system")
            {

            }
            else if(words[0] == "cmd")
            {
                words.removeAt(0);
                astring _command = words.join(" ");
                system(_command.to_chars());
            }
        }
    }
};

#endif // CONSOLE_LOGIC_H
