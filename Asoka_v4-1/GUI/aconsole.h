#ifndef ACONSOLE_H
#define ACONSOLE_H

#include "awidget.h"
#include "DefaultTypes/astring.h"

#include <QKeyEvent>
#include <QTextEdit>


class AConsole : public QTextEdit
{
    Q_OBJECT
public:
    AConsole(AWidget* parent = nullptr) : QTextEdit(parent)
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::Tool | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setMouseTracking(true);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        switch(event->key())
        {
            case(Qt::Key_Enter):
            {
                QString text = toPlainText();
                int sPos = text.lastIndexOf(":> ") + 3;
                int lenth = text.size() - sPos;
                astring command = text.mid(sPos, lenth);
                newCommand(command);
                break;
            }
            case(Qt::Key_Colon):
            {
                QString text = toPlainText();
                setText(text.remove(text.size() - 1, 1));
            }

        }
    }

private:


public slots:

signals:
    void newCommand(astring command);

};

#endif // ACONSOLE_H
