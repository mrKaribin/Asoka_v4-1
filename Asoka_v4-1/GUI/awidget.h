#ifndef AWIDGET_H
#define AWIDGET_H

#include <QLabel>


class AWidget : public QLabel
{
    Q_OBJECT
public:
    AWidget(AWidget* parent = nullptr) : QLabel(parent)
    {
        setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::Tool | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setMouseTracking(true);
    }

private:

};

#endif // AWIDGET_H
