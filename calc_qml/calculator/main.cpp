#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include "appcore.h"

#include "myvalidator.h"
//#include "controller.h"

/*
class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
};
*/

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qmlRegisterType<MyValidator>("MyValidator", 1, 0, "MyValidator");

    AppCore appCore;

    QQmlContext *contxt=engine.rootContext();
    contxt->setContextProperty("appCore", &appCore);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));



    return app.exec();
}
