#ifndef MYVALIDATOR_H
#define MYVALIDATOR_H


#include <Qt>

#include <qvalidator.h>
#include <qregexp.h>

#include <QStringList>

//#include "defs.h"

class MyValidator : public QValidator
{
    Q_OBJECT

public:
    explicit MyValidator(QObject *parent = 0);

    virtual State validate (QString &input, int &pos) const override;


    void fixup(QString & input) const override;
    QLocale locale() const;
    void setLocale(const QLocale & locale);



signals:
    void signalLog(QString text, QString color) const; // text and color
};

#endif // MYVALIDATOR_H
