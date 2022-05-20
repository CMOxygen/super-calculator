#ifndef METHODSQUARES_H
#define METHODSQUARES_H

#include "mathservice.h"

#include <QObject>
#include <QMap>

class MethodSquares : public QObject
{
    Q_OBJECT
public:
    explicit MethodSquares(QObject *parent = nullptr);

   static QMap<double, double> solveSquares(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit);

signals:

};

#endif // METHODSQUARES_H
