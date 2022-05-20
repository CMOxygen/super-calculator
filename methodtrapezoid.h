#ifndef METHODTRAPEZOID_H
#define METHODTRAPEZOID_H

#include <QObject>
#include <QMap>

class MethodTrapezoid : public QObject
{
    Q_OBJECT
public:
    explicit MethodTrapezoid(QObject *parent = nullptr);

    static QMap<double, double> solveTrapeziod(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit);

signals:

};

#endif // METHODTRAPEZOID_H
