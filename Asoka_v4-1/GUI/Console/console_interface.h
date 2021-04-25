#ifndef CONSOLE_H
#define CONSOLE_H

#include "GUI/aconsole.h"
#include "console_logic.h"

#include <QBoxLayout>
#include <QApplication>
#include <QScreen>

class ConsoleInterface : public AWidget
{
    Q_OBJECT

public:
    ConsoleInterface(ConsoleLogic* logic)
    {
        QRect screen = QApplication::screens()[0]->geometry();

        console = new AConsole(this);
        QSize console_size(screen.width() * 0.4, screen.height() * 0.4);
        QPoint console_position(0, 0);
        QRect console_geometry(console_position, console_size);
        connect(console, &AConsole::newCommand, logic, &ConsoleLogic::runCommand);

        QSize my_size(screen.width() * 0.4, screen.height() * 0.4);
        QPoint my_position((screen.width() - my_size.width()) / 2, (screen.height() - my_size.height()) / 2);
        QRect my_geometry(console_position, console_size);

        console->setFixedSize(console_size);
        console->setGeometry(console_geometry);

        setFixedSize(my_size);
        setGeometry(my_geometry);
    }

    ~ConsoleInterface()
    {

    }

private:
    AConsole* console = nullptr;

};

#endif // CONSOLE_H
