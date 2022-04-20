#ifndef METHODSIMPSON_H
#define METHODSIMPSON_H

#include <QObject>

#include <QtScript/QScriptEngine>

class MethodSimpson : public QObject
{
    Q_OBJECT
public:
    explicit MethodSimpson(QObject *parent = nullptr);

    static void solve(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit);
    static double countY(QString func, double x);

signals:

private:

};

#endif // METHODSIMPSON_H
