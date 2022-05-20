#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTableWidget>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->userInputLine->setValidator(new QRegExpValidator(QRegExp("[0-9x+-/*.]*"), ui->userInputLine));
    ui->bottomLimitEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.]*")));
    ui->topLimitEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.]*")));
    ui->stepSizeEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.]*")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solveButton_clicked()
{
    ui->tableWidget->setRowCount(0);

    QString func = ui->userInputLine->text() + '\n';
    double bottomLimit = ui->bottomLimitEdit->text().toDouble();
    double topLimit = ui->topLimitEdit->text().toDouble();
    double delta = topLimit - bottomLimit;

    double stepSize;
    double stepCount;

    QMap<double, double> outputSimpson;

    if (ui->stepTypeBox->currentIndex() == 0)
    {
        stepCount = ui->stepSizeEdit->text().toDouble();
        stepSize = delta / stepCount;
    }

    if (ui->stepTypeBox->currentIndex() == 1)
    {
        stepSize = ui->stepSizeEdit->text().toDouble();
        stepCount = delta / stepSize;
    }

    switch (ui->integrationMethodBox->currentIndex())
    {
    case 0:
    {
        outputSimpson = MethodSquares::solveSquares(func, stepSize, stepCount, bottomLimit, topLimit);
        ui->resultTextBrowser->setText("Решение с помощью " + ui->integrationMethodBox->currentText() + "...");

        int counter = 0;

        auto it = outputSimpson.constBegin();
        auto end = outputSimpson.constEnd();

        QStringList formula{"I = \n", QString::number(stepSize), "*("};

        while (it != end)
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(counter, 0, new QTableWidgetItem(QString::number(counter)));
            ui->tableWidget->setItem(counter, 1, new QTableWidgetItem(QString::number(it.key())));
            ui->tableWidget->setItem(counter, 2, new QTableWidgetItem(QString::number(it.value())));

            if (counter < stepCount)
            {
                formula.append(QString::number(it.value()) + "+");
            }
            ++it;
            counter++;
        }
        formula[formula.length() - 1].replace("+", "");
        formula.append(") = ");
        formula.append(QString::number(MathService::rslt));

        ui->resultTextBrowser->setText(formula.join(""));
        outputSimpson = MethodSquares::solveSquares(func, stepSize, stepCount, bottomLimit, topLimit);
        break;
    }
    case 1:
    {
        outputSimpson = MethodTrapezoid::solveTrapeziod(func, stepSize, stepCount, bottomLimit, topLimit);
        ui->resultTextBrowser->setText("Решение с помощью " + ui->integrationMethodBox->currentText() + "...");

        int counter = 0;

        auto it = outputSimpson.constBegin();
        auto end = outputSimpson.constEnd();

        double firstValue = it.value();
        double lastValue;

        QStringList formula{"I = \n", QString::number(stepSize), "*("};

        while (it != end)
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(counter, 0, new QTableWidgetItem(QString::number(counter)));
            ui->tableWidget->setItem(counter, 1, new QTableWidgetItem(QString::number(it.key())));
            ui->tableWidget->setItem(counter, 2, new QTableWidgetItem(QString::number(it.value())));
            lastValue = it.value();

            if (counter > 0 && counter < stepCount
                    )
            {
                formula.append(QString::number(it.value()) + "+");
            }

            counter++;
            ++it;
        }
        formula[formula.length() - 1].replace("+", "");
        formula.append(")+\n+(" + QString::number(firstValue) + "+" + QString::number(lastValue) + ")/2");
        formula.append(" = ");
        formula.append(QString::number(MathService::rslt));

        ui->resultTextBrowser->setText(formula.join(""));
        break;
    }

    case 2:
    {
        outputSimpson =  MethodSimpson::solveSimpson(func, stepSize, stepCount, bottomLimit, topLimit);
        ui->resultTextBrowser->setText("Решение с помощью " + ui->integrationMethodBox->currentText() + "...");

        int counter = 0;

        double lastValue;

        auto it = outputSimpson.constBegin();
        auto end = outputSimpson.constEnd();

        QStringList formula{"I = \n", QString::number(stepSize), "/3(" , QString::number(it.value())};

        QStringList odds{"+4("};
        QStringList evens{"\n+2("};

        while (it != end)
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
            ui->tableWidget->setItem(counter, 0, new QTableWidgetItem(QString::number(counter)));
            ui->tableWidget->setItem(counter, 1, new QTableWidgetItem(QString::number(it.key())));
            ui->tableWidget->setItem(counter, 2, new QTableWidgetItem(QString::number(it.value())));

            if (counter > 0 && counter < stepCount)
            {
                counter % 2 == 0 ? evens.append(QString::number(it.value()) + "+") : odds.append(QString::number(it.value()) + "+");
            }
            if (counter == stepCount)
            {
                lastValue = it.value();
            }
            counter++;
            ++it;
        }

        evens[evens.length() - 1].replace("+", "");
        odds[odds.length() - 1].replace("+", "");
        odds.append(")+");
        evens.append(")");

        formula.append(odds);
        formula.append(evens);

        formula.append("+");
        formula.append(QString::number(lastValue));
        formula.append(") = ");
        formula.append(QString::number(MathService::rslt));

        ui->resultTextBrowser->setText(formula.join(""));
        break;
    }
    }
}
