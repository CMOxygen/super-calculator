#include "methodtrapezoid.h"

#include "mathservice.h"

#include <QDebug>

MethodTrapezoid::MethodTrapezoid(QObject *parent) : QObject(parent)
{

}

QMap <double, double> MethodTrapezoid::solveTrapeziod(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit)
{
    QMap <double, double> values;

    for (int i = 0; i <= stepCount; i++)
    {
        values[bottomLimit] = MathService::parseFunc(func, bottomLimit);
        bottomLimit += stepSize;
    }
    double beginValue;
    double endValue;


    auto it = values.constBegin();
    auto end = --values.constEnd();
    beginValue = it.value();
    endValue = end.value();

    it++;
    double sum1 = (beginValue + endValue) / 2;
    double sum2 = 0;

    while (it != end)
    {
        sum2+=it.value();
        it++;
    }
    MathService::rslt = stepSize * (sum1 + sum2);
    return values;
}
