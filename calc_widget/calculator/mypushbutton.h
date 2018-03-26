#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <qpushbutton.h>

class MyPushButton : public QPushButton
{
    Q_OBJECT

public:
    MyPushButton():QPushButton()
    {
        connect(this, SIGNAL(released()), this, SLOT(slotReleasedButton()));
    }
public slots:
    void slotReleasedButton()
    {
        // вместе с отжатием кнопки передается название кнопки
        emit signalReleased(this->text());
    }

signals:
    void signalReleased(QString);
};

#endif // MYPUSHBUTTON_H
