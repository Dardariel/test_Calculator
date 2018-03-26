#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec* c = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(c);
    QTextCodec::setCodecForCStrings(c);
    QTextCodec::setCodecForLocale(c);

    MainWindow w;
    w.show();

    return a.exec();
}
