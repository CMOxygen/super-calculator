#ifndef METHODSIMPSON_H
#define METHODSIMPSON_H

#include "mathservice.h"

#include <QObject>

class MethodSimpson : public QObject
{
    Q_OBJECT
public:
    explicit MethodSimpson(QObject *parent = nullptr);

    static QMap<double, double> solveSimpson(QString func, double stepSize, double stepCount, double bottomLimit, double topLimit);

signals:

private:

};

#endif // METHODSIMPSON_H
