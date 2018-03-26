#include "mythread.h"

#include <QTime>

void MyThread::run()
{
    QTime time;
    int time_left;
    int type;
    double a, b;
    unsigned long long num;
    double res;
    int err;
    while(1)
    {

        if(mq_Req->get(type, a, b, num)==MQ_NO_ERROR)
        {
            time=QTime::currentTime();
            res=DoIt(type, a, b, err);

            time_left=mSec-time.elapsed(); // расчет отатка времени ожидания с учетом времени выполнения вычислений
            if(time_left>0)
            {
                this->msleep(time_left);
            }

            if(err==LMM_ERROR_DIVISION_BY_ZERO)
            {
                mq_Res->set("Ошибка: деление на ноль запрещено", num);
            }
            else if(err==LMM_ERROR_INVALID_OPERATION)
            {
                mq_Res->set("Ошибка: недопустимая операция", num);
            }
            else
            {
                mq_Res->set(QString::number(res, 'g', 15), num);
            }
        }

        else
        {
            this->usleep(100); // что бы процесс в режиме ожидания не поглощал лишние ресурсы процессора
        }
// для примера можно сравнить нагрузку на процессор утилитой top с этой стройкой и без

    }
}

void MyThread::setTimer(double sec)
{
        mSec=(int)(sec*1000.0);
}

void MyThread::setQueue(MyQueueRequests *req, MyQueueResults *res)
{
    if(!isRunning())
    {
        mq_Req=req;
        mq_Res=res;
    }
}
