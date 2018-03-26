#include "mainwindow.h"

#include <Qt>
#include <QGridLayout>
#include <QScrollBar>

#include "myvalidator.h"
#include "my_math_lib.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Number=1;
    QSize sz;
    sz.setHeight(40);
    sz.setWidth(40);

    setWindowTitle("Калькулятор");

    QWidget *placeholderWidget = new QWidget;

    // инициализация таймера
    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), SLOT(slotTimeout()));

    // инициализация очередей
    mq_Req=new MyQueueRequests;
    connect(mq_Req, SIGNAL(signalChangeCount(int)), SLOT(slotChangeReq(int)));

    mq_Res=new MyQueueResults;
    connect(mq_Res, SIGNAL(signalChangeCount(int)), SLOT(slotChangeRes(int)));

    // инициализация потока
    thread = new MyThread();
    thread->setQueue(mq_Req, mq_Res);

    // инициализация и настройка элементов графического окна
    le_Line = new QLineEdit();
    //connect(le_Line, SIGNAL(editingFinished()), SLOT(slotResult()));
    MyValidator *vl = new MyValidator(le_Line);
    connect(vl, SIGNAL(signalLog(QString,int,int)), SLOT(slotLog(QString,int,int)));
    le_Line->setValidator(vl);

    tw_Log = new QTreeWidget;
    tw_Log->setColumnCount(2);
    tw_Log->headerItem()->setHidden(true);
    tw_Log->expandAll();
    tw_Log->hideColumn(1);

    for(int i=0; i<10; i++)
    {
        pb_Numbers[i]=new MyPushButton();
        pb_Numbers[i]->setText(QString::number(i));
        pb_Numbers[i]->setMaximumSize(sz);
        pb_Numbers[i]->setMinimumSize(sz);
        connect(pb_Numbers[i], SIGNAL(signalReleased(QString)), SLOT(slotAddSymbol(QString)));
    }

    pb_Plus=new MyPushButton();
    pb_Plus->setText("+");
    pb_Plus->setMaximumSize(sz);
    pb_Plus->setMinimumSize(sz);
    connect(pb_Plus, SIGNAL(signalReleased(QString)), SLOT(slotAddSymbol(QString)));

    pb_Minus=new MyPushButton();
    pb_Minus->setText("-");
    pb_Minus->setMaximumSize(sz);
    pb_Minus->setMinimumSize(sz);
    connect(pb_Minus, SIGNAL(signalReleased(QString)), SLOT(slotAddSymbol(QString)));

    pb_Multiply=new MyPushButton();
    pb_Multiply->setText("*");
    pb_Multiply->setMaximumSize(sz);
    pb_Multiply->setMinimumSize(sz);
    connect(pb_Multiply, SIGNAL(signalReleased(QString)), SLOT(slotAddSymbol(QString)));

    pb_Divide=new MyPushButton();
    pb_Divide->setText("/");
    pb_Divide->setMaximumSize(sz);
    pb_Divide->setMinimumSize(sz);
    connect(pb_Divide, SIGNAL(signalReleased(QString)), SLOT(slotAddSymbol(QString)));

    pb_Dot=new MyPushButton();
    pb_Dot->setText(".");
    pb_Dot->setMaximumSize(sz);
    pb_Dot->setMinimumSize(sz);
    connect(pb_Dot, SIGNAL(signalReleased(QString)), SLOT(slotAddSymbol(QString)));

    pb_C=new QPushButton();
    pb_C->setText("C");
    pb_C->setMaximumSize(sz);
    pb_C->setMinimumSize(sz);
    connect(pb_C, SIGNAL(released()), SLOT(slotC()));

    pb_Backspace=new QPushButton();
    pb_Backspace->setText("<-");
    pb_Backspace->setMaximumSize(sz);
    pb_Backspace->setMinimumSize(sz);
    connect(pb_Backspace, SIGNAL(released()), SLOT(slotBackspace()));

    pb_Result=new QPushButton();
    pb_Result->setText("=");
    pb_Result->setMaximumSize(sz);
    pb_Result->setMinimumSize(sz);
    connect(pb_Result, SIGNAL(released()), SLOT(slotResult()));

    // настройка виджетов работы с очередями и таймерами

    l_Req = new QLabel();
    l_Req->setMaximumHeight(20);
    l_Req->setText("Req: 0");

    l_Res = new QLabel();
    l_Res->setMaximumHeight(20);
    l_Res->setText("Res: 0");

    sb_TimerRes = new QDoubleSpinBox();
    sb_TimerRes->setSuffix(" с");
    sb_TimerRes->setMaximum(100.0);
    sb_TimerRes->setDecimals(4);
    sb_TimerRes->setSingleStep(0.01);
    connect(sb_TimerRes, SIGNAL(valueChanged(double)), SLOT(slotChangeTimer(double)));

    sb_TimerReq = new QDoubleSpinBox();
    sb_TimerReq->setSuffix(" с");
    sb_TimerReq->setMaximum(100.0);
    sb_TimerReq->setDecimals(4);
    sb_TimerReq->setSingleStep(0.01);
    connect(sb_TimerReq, SIGNAL(valueChanged(double)), thread, SLOT(setTimer(double)));

    // размещение графических элементов

    QGridLayout *grid = new QGridLayout(placeholderWidget);

    grid->addWidget(tw_Log, 0, 0, 8, 1);

    grid->addWidget(le_Line, 0, 1, 1, 5);

    grid->addWidget(pb_Numbers[7], 1, 1);
    grid->addWidget(pb_Numbers[8], 1, 2);
    grid->addWidget(pb_Numbers[9], 1, 3);
    grid->addWidget(pb_Divide, 1, 4);
    grid->addWidget(pb_C, 1, 5);

    grid->addWidget(pb_Numbers[4], 2, 1);
    grid->addWidget(pb_Numbers[5], 2, 2);
    grid->addWidget(pb_Numbers[6], 2, 3);
    grid->addWidget(pb_Multiply, 2, 4);
    grid->addWidget(pb_Backspace, 2, 5);

    grid->addWidget(pb_Numbers[1], 3, 1);
    grid->addWidget(pb_Numbers[2], 3, 2);
    grid->addWidget(pb_Numbers[3], 3, 3);
    grid->addWidget(pb_Minus, 3, 4);

    grid->addWidget(pb_Numbers[0], 4, 1);
    grid->addWidget(pb_Dot, 4, 2);
    grid->addWidget(pb_Plus, 4, 4);
    grid->addWidget(pb_Result, 4, 5);

    grid->addWidget(l_Req, 6, 1, 1, 2);
    grid->addWidget(l_Res, 6, 3, 1, 2);
    grid->addWidget(sb_TimerReq, 7, 1, 1, 2);
    grid->addWidget(sb_TimerRes, 7, 3, 1, 2);

    placeholderWidget->setLayout(grid);
    setCentralWidget(placeholderWidget);

    // Инициализация и чтение ранее используемых значений

    Settings = new QSettings("./calculator.conf",  QSettings::NativeFormat, this);
    readSetting();

    // запуск таймера и потока
    Timer->start();
    thread->start(QThread::NormalPriority);

}
//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    thread->terminate();
    writeSetting();
}
//----------------------------------------------------------------------------
// добавление символа к строке
void MainWindow::slotAddSymbol(QString s)
{
    le_Line->insert(s);
}
//----------------------------------------------------------------------------
// удаление последнего символа в строке
void MainWindow::slotBackspace()
{
    // проверка на пустую строку
    if(!le_Line->text().length())
    {
        slotLog("Ошибка: строка примера пустая", LOG_ERROR, 0);
        return;
    }
    le_Line->backspace();
}
//----------------------------------------------------------------------------
// очистка строки
void MainWindow::slotC()
{
    // проверка на пустую строку
    if(!le_Line->text().length())
    {
        slotLog("Ошибка: строка примера пустая", LOG_ERROR, 0);
        return;
    }
    le_Line->clear();
}
//----------------------------------------------------------------------------
// передача примера для расчета
void MainWindow::slotResult()
{
    QRegExp re;
    re.setPattern("[+\\-\\*\\/]");
    QStringList lst;
    QString str;
    bool minus=false;
    int operation;

    // проверка на пустую строку
    if(!le_Line->text().length())
    {
        slotLog("Ошибка: строка примера пустая", LOG_ERROR, 0);
        return;
    }

    str=le_Line->text();

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
        slotLog("Ошибка: формат примера не корректен", LOG_ERROR, 0);
        return;
    }
    for(int i=0; i<lst.count(); i++)
    {
        if(lst.at(i).length()==0)
        {
            slotLog("Ошибка: формат примера не корректен", LOG_ERROR, 0);
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

    slotLog(le_Line->text(), LOG_CALC, Number++);

    if(Number==0)
    {
        Number=1;
    }
    slotC();
}
//----------------------------------------------------------------------------
// настройка таймера получения ответа
void MainWindow::slotChangeTimer(double sec)
{
    Timer->start((int)(sec*1000.0));
}
//----------------------------------------------------------------------------
// обработка таймера получения ответа
void MainWindow::slotTimeout()
{
    QString res;
    QList<QTreeWidgetItem *> ltwi;
    unsigned long long num;

    if(mq_Res->get(res, num)==MQ_NO_ERROR)
    {
        ltwi=tw_Log->findItems(QString::number(num, 'g', 15), Qt::MatchExactly, 1);
        for(int i=0;i<ltwi.count();i++)
        {
            ltwi.at(i)->setText(0, ltwi.at(i)->text(0)+" = "+res);
            if(res.contains("Ошибка"))
            {
                ltwi.at(i)->setTextColor(0, QColor(Qt::darkRed));
            }
            else
            {
                ltwi.at(i)->setTextColor(0, QColor(Qt::blue));
            }
        }
    }
}
//----------------------------------------------------------------------------
// ведение лога
void MainWindow::slotLog(QString str, int status, int num)
{

    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, str);
    item->setText(1, QString::number(num, 'g', 15));
    tw_Log->addTopLevelItem(item);

    if(tw_Log->verticalScrollBar()->maximum()==tw_Log->verticalScrollBar()->value())
    {
        tw_Log->scrollToBottom();
    }

    switch (status)
    {
    case LOG_ERROR:
        item->setTextColor(0, QColor(Qt::red));
        return;
    case LOG_CALC:
        item->setTextColor(0, QColor(Qt::darkGreen));
        return;

    }
}
//----------------------------------------------------------------------------
// обработчик сигнала о изменении количества из очереди ответов
void MainWindow::slotChangeRes(int count)
{
    l_Res->setText("Res: "+QString::number(count));
}
//----------------------------------------------------------------------------
// обработчик сигнала о изменении количества из очереди заданий
void MainWindow::slotChangeReq(int count)
{
    l_Req->setText("Req: "+QString::number(count));
}
//----------------------------------------------------------------------------
// запись параметров в файл
void MainWindow::writeSetting()
{
    Settings->beginGroup("/frame");

    Settings->setValue("geometry", saveGeometry());
    Settings->setValue("savestate", saveState());
    Settings->setValue("maximized", isMaximized());
    if (!isMaximized())
    {
        Settings->setValue("pos", pos());
        Settings->setValue("size", size());
    }
    Settings->endGroup();

    Settings->beginGroup("/timer");
    Settings->setValue("/queue_timer_req", sb_TimerReq->value());
    Settings->setValue("/queue_timer_res", sb_TimerRes->value());
    Settings->endGroup();

}
//----------------------------------------------------------------------------
// чтение и применение параметров из файла
void MainWindow::readSetting()
{

    Settings->beginGroup("/frame");

    restoreGeometry(Settings->value("geometry", saveGeometry()).toByteArray());
    restoreState(Settings->value("savestate", saveState()).toByteArray());
    move(Settings->value("pos", pos()).toPoint());
    resize(Settings->value("size", size()).toSize());
    if (Settings->value("maximized", isMaximized()).toBool())
    {
        showMaximized();
    }
    Settings->endGroup();


    Settings->beginGroup("/timer");
    sb_TimerReq->setValue(Settings->value("/queue_timer_req","1").toDouble());
    sb_TimerRes->setValue(Settings->value("/queue_timer_res","1").toDouble());
    Settings->endGroup();
}
