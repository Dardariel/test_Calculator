#include "appcore.h"
#include "my_math_lib.h"

#include <QRegExp>

#include <QDebug>

AppCore::AppCore(QObject *parent) : QObject(parent)
{
    Number=1;

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), SLOT(slotTimeout()));

    // инициализация очередей
    mq_Req=new MyQueueRequests;
    //connect(mq_Req, SIGNAL(signalChangeCount(int)), SLOT(slotChangeReq(int)));
    connect(mq_Req, SIGNAL(signalChangeCount(int)), SIGNAL(sendToQmlReq(int)));

    mq_Res=new MyQueueResults;
    //connect(mq_Res, SIGNAL(signalChangeCount(int)), SLOT(slotChangeRes(int)));
    connect(mq_Res, SIGNAL(signalChangeCount(int)), SIGNAL(sendToQmlRes(int)));

    // инициализация потока
    thread = new MyThread();
    thread->setQueue(mq_Req, mq_Res);
    connect(this, SIGNAL(signalChangeTimeInterval(int)), thread, SLOT(setTimer(int)));

    // запуск таймера и потока
    Timer->start(100);
    thread->start(QThread::NormalPriority);



}


void AppCore::qmlResult(QString text)
{
    qDebug()<<text;

    QRegExp re;
    re.setPattern("[+\\-\\*\\/]");
    QStringList lst;
    QString str;
    bool minus=false;
    int operation;

    // проверка на пустую строку
    if(!text.length())
    {
        slotLog("Ошибка: строка примера пустая", "red");
        return;
    }

    str=text;

    // проверка первого символа
    if(str.at(0)==QChar('-'))
    {
        minus=true;
        str.remove(0,1);
    }
    // проверка законченности уравнения
    lst = str.split(re);
    if(lst.count()!=2)
    {
        slotLog("Ошибка: формат примера не корректен", "red");
        return;
    }
    for(int i=0; i<lst.count(); i++)
    {
        if(lst.at(i).length()==0)
        {
            slotLog("Ошибка: формат примера не корректен", "red");
            return;
        }
    }

    // определение типа операции
    if(str.contains("+"))
    {
        operation=LMM_OPERATION_PLUS;
    }
    else if(str.contains("-"))
    {
        operation=LMM_OPERATION_MINUS;
    }
    else if(str.contains("*"))
    {
        operation=LMM_OPERATION_MULTIPLY;
    }
    else
    {
        operation=LMM_OPERATION_DIVIDE;
    }

    // подготовка данных
    if(minus)
    {
        str="-"+lst.at(0);
    }
    else
    {
        str=lst.at(0);
    }

    // передача значений в очередь для расчета
    mq_Req->set(operation, str.toDouble(), lst.at(1).toDouble(), Number);

    slotLog("Передано для вычисления #"+QString::number(Number++, 'g', 15)+": "+text, "darkgreen");

    if(Number==0)
    {
        Number=1;
    }
}

void AppCore::qmlTimerChangeReq(int value)
{
    emit signalChangeTimeInterval(value);
}
void AppCore::qmlTimerChangeRes(int value)
{
    Timer->start(value);
}
void AppCore::slotLog(QString text, QString color)
{
    emit sendToQmlLog(text, color);
}

void AppCore::slotTimeout()
{
    QString res;
    unsigned long long num;

    if(mq_Res->get(res, num)==MQ_NO_ERROR)
    {
        if(res.contains("Ошибка"))
        {
            slotLog("Результат вычислений #"+QString::number(num, 'g', 15)+": "+res, "darkred");
        }
        else
        {
            slotLog("Результат вычислений #"+QString::number(num, 'g', 15)+": "+res, "blue");
        }
    }
}
