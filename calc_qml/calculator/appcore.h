#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <QTimer>

#include "mythread.h"
#include "myqueue.h"

class AppCore : public QObject
{
    Q_OBJECT
public:
    explicit AppCore(QObject *parent = nullptr);

    MyThread *thread; // поток для проведения расчетов

    MyQueueRequests *mq_Req; // очередь примеров для расчета
    MyQueueResults *mq_Res; // очередь результатов расчета

    QTimer *Timer;

signals:
    // Сигналы для передачи данных в qml-интерфейс
    void sendToQmlLog(QString text, QString color);
    void sendToQmlReq(int count);
    void sendToQmlRes(int count);

    // Сигналы для взаимодействия между объектами
    void signalChangeTimeInterval(int);

public slots:
    void qmlResult(QString text);

    void qmlTimerChangeReq(int value);
    void qmlTimerChangeRes(int value);

    void slotLog(QString text, QString color);

    void slotTimeout();

private:
    unsigned long long Number;
};

#endif // APPCORE_H
