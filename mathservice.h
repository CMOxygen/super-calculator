#ifndef MATHSERVICE_H
#define MATHSERVICE_H

#include <QObject>

class MathService : public QObject
{
    Q_OBJECT
public:
    explicit MathService(QObject *parent = nullptr);

    static double parseFunc(QString input, double x);

    static bool mapContainsValue(QMap<int, int> in, int value);
    static bool isNumber(QString str);

    static double calculate(QList<QString> in, double x);

    static double rslt;

private:
    static const double PI;
    static const double E;

signals:

};

#endif // MATHSERVICE_H
