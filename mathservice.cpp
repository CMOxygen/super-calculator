#include "mathservice.h"

#include <QDebug>

MathService::MathService(QObject *parent) : QObject(parent)
{

}
const double MathService::PI = 3.141593;
const double MathService::E = 2.718282;

double MathService::rslt;

double MathService::parseFunc(QString input, double x)
{
    QList<QChar> lettersList = {'p', 'i', 'e'};
    QList<QString> funcExpressions;
    QString buffDigits = "";
    QString buffExpressions = "";

    QMap<int, int> bracketPairIndexes;

    for (QChar c : input)
    {
        if(c.isDigit() || c == '.')
        {
            buffDigits.append(c);
        }
        else if (c == 'x')
        {
            funcExpressions.append(c);
        }
        else if(lettersList.contains(c))
        {
            buffExpressions.append(c);
        }
        else
        {
            if(buffDigits.length() > 0)
            {
                funcExpressions.append(buffDigits);
            }
            if(buffExpressions.length() > 0)
            {
                funcExpressions.append(buffExpressions);
            }
            buffDigits = "";
            buffExpressions = "";

            if(c != '\n')
            {
                funcExpressions.append(c);
            }
        }
    }
    double result = calculate(funcExpressions, x);
    return result;
}

bool MathService::mapContainsValue(QMap<int, int> in, int value)
{
    QMap<int, int>::const_iterator it = in.constBegin();
    auto end = in.constEnd();

    while (it != end)
    {
        if  (it.value() == value) {
            return true;
        }
        ++it;
    }
    return false;
}

bool MathService::isNumber(QString str)
{
    for (QChar c : str) {
        if (!c.isDigit() && c != '.')
        {
            return false;
        }
    }
    return true;
}

double MathService::calculate(QList<QString> in, double x)
{
    QList<QString> mathBuffer;
    QList<QString> bufferToSum;

    QList<int> indexes;

    double result = 1;
    double firstIndex = 0;

    bool calculating = true;

    for (QString s : in)
    {
        if (s == "x")
        {
            mathBuffer.append(QString::number(x));
        }
        else if (s == "pi")
        {
            mathBuffer.append(QString::number(MathService::PI));
        }
        else if (s == "e")
        {
            mathBuffer.append(QString::number(MathService::E));
        }
        else
        {
            mathBuffer.append(s);
        }
    }
    if (mathBuffer.contains("*") || mathBuffer.contains("/"))
    {
        while (calculating)
        {
            calculating = false;

            for (int i = firstIndex; i < mathBuffer.length(); i++)
            {
                if (mathBuffer[i] == "*" || mathBuffer[i] == "/")
                {
                    result = mathBuffer[i - 1].toDouble();
                    firstIndex = i - 1;
                    indexes.append(i - 2);
                    indexes.append(i - 1);
                    break;
                }
            }

            for (int i = firstIndex; i < mathBuffer.length(); i++)
            {
                if (mathBuffer[i] == "*")
                {
                    result *= mathBuffer[i + 1].toDouble();
                    calculating = true;
                    indexes.append(i);
                    indexes.append(i + 1);
                }
                if (mathBuffer[i] == "/")
                {
                    result /= mathBuffer[i + 1].toDouble();
                    calculating = true;
                    indexes.append(i);
                    indexes.append(i + 1);
                }
                if (mathBuffer[i] == "+" || mathBuffer[i] == "-" || i == mathBuffer.length() - 1)
                {
                    if (mathBuffer[firstIndex - 1] == "+" || mathBuffer[firstIndex - 1] == "-")
                    {
                        bufferToSum.append(mathBuffer[firstIndex - 1]);
                    }
                    else
                    {
                        bufferToSum.append("+");
                    }
                    bufferToSum.append(QString::number(result));
                    firstIndex = i;
                    result = 1;
                    break;
                }
            }
        }
        bufferToSum.removeLast();
        bufferToSum.removeLast();
    }
    result = 0;

    if (mathBuffer.contains("+") || mathBuffer.contains("-"))
    {
        for (int i = 0; i < mathBuffer.length(); i++)
        {
            if (mathBuffer[i] == "+" && !indexes.contains(i))
            {
                if (result == 0)
                {
                    result = mathBuffer[i - 1].toDouble() + mathBuffer[i + 1].toDouble();
                }
                else
                {
                    result += mathBuffer[i + 1].toDouble();
                }
            }

            if (mathBuffer[i] == "-" && !indexes.contains(i))
            {
                if (result == 0)
                {

                    result = mathBuffer[i - 1].toDouble() - mathBuffer[i + 1].toDouble();
                }
                else
                {
                    result -= mathBuffer[i + 1].toDouble();
                }
            }
        }
    }
    for (int i = 0; i < bufferToSum.length(); i+=2)
    {
        result += bufferToSum.mid(i, 2).join("").toDouble();
    }
    return result;
}
