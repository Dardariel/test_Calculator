#ifndef MYQUEUE
#define MYQUEUE

// Thread safe string queue

#include <QObject>
#include <QMutex>
#include <QQueue>
#include <QPair>

#define MQ_NO_ERROR 0
#define MQ_QUEUE_EMPTY 1

// объект очереди результатов
class MyQueueResults : public QObject
{
    Q_OBJECT

private:
    // Мьютекс для разграничения доступа к очереди
    QMutex	m_Mutex;

    // очередь пар номера операции и решения
    QQueue< QPair <unsigned long long, QString> > qp_Queue;

public:
    MyQueueResults() : QObject()
    {
    }

    // функция введения нового элемента
    void set(const QString &res, const unsigned long long &num)
    {
        m_Mutex.lock();
        QPair<unsigned long long, QString> pair;
        pair.first=num;
        pair.second=res;
        qp_Queue.enqueue(pair);
        m_Mutex.unlock();
        emit signalChangeCount(qp_Queue.count());
    }

    // функция изъятия первого значения из очереди
    int get(QString &res, unsigned long long &num)
    {
        QMutexLocker locker (&m_Mutex);
        QPair<unsigned long long, QString> pair;
        if(qp_Queue.empty())
        {
            return MQ_QUEUE_EMPTY;
        }
        pair=qp_Queue.dequeue();
        res=pair.second;
        num=pair.first;
        emit signalChangeCount(qp_Queue.count());
        return MQ_NO_ERROR;
    }

signals:
    void signalChangeCount(int);
};

// структура данных для передачи задания
struct MyTask
{
    int TypeWork; // тип операции
    double OperandA; // А
    double OperandB; // В
    unsigned long long Number; // номер операции
};

// объект очереди заданий
class MyQueueRequests : public QObject
{
    Q_OBJECT

private:
    QMutex	m_Mutex;
    QQueue<MyTask> qp_Queue;

public:
    MyQueueRequests() : QObject()
    {
    }
   void set(const int &type, const double &a, const double &b, const unsigned long long &num)
    {
        m_Mutex.lock();
        MyTask t;
        t.TypeWork=type;
        t.OperandA=a;
        t.OperandB=b;
        t.Number=num;
        qp_Queue.enqueue(t);
        m_Mutex.unlock();
        emit signalChangeCount(qp_Queue.count());
    }

    int get(int &type, double &a, double &b, unsigned long long &num)
    {
        QMutexLocker locker (&m_Mutex);
        MyTask t;
        if(qp_Queue.empty())
        {
            return MQ_QUEUE_EMPTY;
        }
        t=qp_Queue.dequeue();
        type=t.TypeWork;
        a=t.OperandA;
        b=t.OperandB;
        num=t.Number;
        emit signalChangeCount(qp_Queue.count());
        return MQ_NO_ERROR;
    }
signals:
    void signalChangeCount(int);
};


#endif // MYQUEUE

