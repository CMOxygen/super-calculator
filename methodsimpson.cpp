#include "methodsimpson.h"

#include <QDebug>

MethodSimpson::MethodSimpson(QObject *parent) : QObject(parent)
{
}

void MethodSimpson::solve(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit)
{

    qDebug() << func;
    double x = bottomLimit;

    double y;

    for(int i = 0; i < stepCount; i++)
    {
        qDebug() << i << x;

        x+=stepSize;
    }
    MethodSimpson::countY(func, x);
}

double MethodSimpson::countY(QString func, double x)
{
    double y = 0.0;

    QList<double> digits;
    QList<QString> math;
    QList<QString> variables;

    QString buff = "";

    for(QChar c : func)
    {
        if(c.isDigit())
        {
            buff.append(c);
        }
        else if(c=='x')
        {
            variables.append(c);
        }
        else
        {
            if(buff.length()>0)
            {
                digits.append(buff.toDouble());
            }
            buff="";

            if(c!='\n')
            {
                math.append(c);
            }
        }
    }

    qDebug() << "SIMPSON Y " << digits;
    qDebug() << "SIMPSON Y " << variables;
    qDebug() << "SIMPSON Y " << math;

    qDebug() << QString("2+3");

    return 0;
}
