#include "methodsquares.h"

#include <QDebug>

MethodSquares::MethodSquares(QObject *parent) : QObject(parent)
{

}

QMap <double, double> MethodSquares::solveSquares(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit)
{
    QMap <double, double> values;

    for (int i = 0; i <= stepCount; i++)
    {
        values[bottomLimit] = MathService::parseFunc(func, bottomLimit + 0.05);
        bottomLimit += stepSize;
    }
    auto it = values.constBegin();
    auto end = --values.constEnd();

    double sum = 0;

    while (it != end)
    {
        sum+=it.value();
        it++;
    }
    MathService::rslt = stepSize * sum;
    return values;
}
