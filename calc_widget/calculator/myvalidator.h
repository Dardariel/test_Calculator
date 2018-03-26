#ifndef MYVALIDATOR
#define MYVALIDATOR

#include <Qt>

#include <qvalidator.h>
#include <qregexp.h>

#include <QStringList>

#include "defs.h"

class MyValidator : public QValidator
{
    Q_OBJECT

public:
    MyValidator(QObject *parent = 0):QValidator(parent)
    {
    }

    virtual State validate (QString &input, int &) const
    {
        // можно сделать с помощью регулярного выражения,
        // но идентифицировать ошибки будет сложнее,
        // да и регулярки я подзабыл

        int i, j;
        QRegExp re1;
        re1.setPattern("[0-9.+\\-\\*\\/]*");
        QRegExp re2;
        re2.setPattern("[+\\-\\*\\/]");
        QString str;
        QStringList lst, lst2;

        // проверка на пустую строку
        if(!input.length())
        {
            return Acceptable;
        }

        // проверка допустимых символов
        if(!re1.exactMatch(input))
        {
            emit signalLog("Ошибка: недопустимый символ", LOG_ERROR, 0);
            return Invalid;
        }

        str=input;

        // проверка первого символа
        if(str.at(0)==QChar('-'))
        {
            str.remove(0,1);
        }
        else if((str.at(0)==QChar('+'))||(str.at(0)==QChar('*'))||(str.at(0)==QChar('/'))||(str.at(0)==QChar('.')))
        {
            emit signalLog("Ошибка: недопустимый символ", LOG_ERROR, 0);
            return Invalid;
        }

        lst = str.split(re2);
        if(lst.count()>2)
        {
            emit signalLog("Ошибка: недопустимая операция", LOG_ERROR, 0);
            return Invalid;
        }

        // проверка на точку и кол-во симовлов

        for(i=0; i<lst.count(); i++)
        {
            lst2.clear();
            lst2=lst.at(i).split(".");
            if(lst2.count()>2)
            {
                emit signalLog("Ошибка: в числе не может быть 2 точки", LOG_ERROR, 0);
                return Invalid;
            }
            for(j=0; j<lst2.count(); j++)
            {
                if(lst2.at(j).length()>15)
                {
                    emit signalLog("Ошибка: недопустимая длинна числа", LOG_ERROR, 0);
                    return Invalid;
                }
            }
        }
        return Acceptable;
    }

signals:
    void signalLog(QString, int, int) const;
};



#endif // MYVALIDATOR

