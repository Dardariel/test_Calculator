#include "myvalidator.h"

MyValidator::MyValidator(QObject *parent):QValidator(parent)
{
}

QValidator::State MyValidator::validate (QString &input, int &pos) const
{
    Q_UNUSED(pos)

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
        emit signalLog("Ошибка: недопустимый символ", "red");
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
        emit signalLog("Ошибка: недопустимый символ", "red");
        return Invalid;
    }

    lst = str.split(re2);
    if(lst.count()>2)
    {
        emit signalLog("Ошибка: недопустимая операция", "red");
        return Invalid;
    }

    // проверка на точку и кол-во симовлов

    for(i=0; i<lst.count(); i++)
    {
        lst2.clear();
        lst2=lst.at(i).split(".");
        if(lst2.count()>2)
        {
            emit signalLog("Ошибка: в числе не может быть 2 точки", "red");
            return Invalid;
        }
        for(j=0; j<lst2.count(); j++)
        {
            if(lst2.at(j).length()>15)
            {
                emit signalLog("Ошибка: недопустимая длинна числа", "red");
                return Invalid;
            }
        }
    }
    return Acceptable;
}

void MyValidator::fixup(QString & input) const
{
    QValidator::fixup(input);
}

QLocale MyValidator::locale() const
{
    return QValidator::locale();
}

void MyValidator::setLocale(const QLocale & locale)
{
    QValidator::setLocale(locale);
}
