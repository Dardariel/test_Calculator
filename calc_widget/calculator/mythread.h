#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

#include "my_math_lib.h"
#include "myqueue.h"

class MyThread : public QThread
{
    Q_OBJECT

protected:
    void run();

public:
    void setQueue(MyQueueRequests *req, MyQueueResults *res);

public slots:
    void setTimer(double sec);

private:
    unsigned int mSec;
    MyQueueRequests *mq_Req;
    MyQueueResults *mq_Res;


};

#endif // MYTHREAD_H
