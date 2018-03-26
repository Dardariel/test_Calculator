#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTreeWidget>
#include <QTimer>
#include <QLabel>
#include <QSpinBox>
#include <QSettings>

#include "mypushbutton.h"
#include "defs.h"
#include "mythread.h"
#include "myqueue.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    unsigned long long Number;

    QSettings *Settings;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MyPushButton *pb_Numbers[10]; // цифровые кнопки

    MyPushButton *pb_Plus; // кнопки математических операций
    MyPushButton *pb_Minus;
    MyPushButton *pb_Multiply;
    MyPushButton *pb_Divide;

    MyPushButton *pb_Dot; // кнопка точки

    QPushButton *pb_C; // кнопки управления строкой
    QPushButton *pb_Backspace;

    QPushButton *pb_Result; // кнопка передачи на расчет

    QLineEdit *le_Line; // строка подготовки примера

    QTreeWidget *tw_Log; // виджет ведения лога

    QLabel *l_Req;  // виджет отображения состояния очереди
    QLabel *l_Res;

    QDoubleSpinBox *sb_TimerRes; // виджеты для настройки таймеров задержки
    QDoubleSpinBox *sb_TimerReq;

    MyThread *thread; // поток для проведения расчетов

    MyQueueRequests *mq_Req; // очередь примеров для расчета
    MyQueueResults *mq_Res; // очередь результатов расчета

    QTimer *Timer;

    void writeSetting(); // сохранение настроек
    void readSetting();

public slots:
    void slotAddSymbol(QString s);
    void slotC();
    void slotBackspace();
    void slotResult();

    void slotChangeTimer(double sec);
    void slotTimeout();

    void slotChangeRes(int count);
    void slotChangeReq(int count);

    void slotLog(QString str, int status=LOG_INFO,  int num=0);

};

#endif // MAINWINDOW_H
