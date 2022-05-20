#include "methodsimpson.h"

#include <QDebug>

MethodSimpson::MethodSimpson(QObject *parent) : QObject(parent)
{
}

QMap<double, double> MethodSimpson::solveSimpson(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit)
{
    QMap<double, double> values;

    for (int i = 0; i <= stepCount; i++)
    {
        values[bottomLimit] = MathService::parseFunc(func, bottomLimit);
        bottomLimit += stepSize;
    }
    double evens = 0;
    double odds = 0;
    double beginValue;
    double endValue;

    auto it = ++values.constBegin();
    auto end = --values.constEnd();
    int counter = 1;

    beginValue = it.value();
    endValue = end.value();

    while (it != end)
    {
        counter % 2 == 0 && counter < stepCount - 1 ? evens += it.value() : odds += it.value();
        counter++;
        it++;
    }
    MathService::rslt = stepSize / 3 * (beginValue + 4 * odds + 2 * evens + endValue);
    return values;
}
