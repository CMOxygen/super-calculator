#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->userInputLine->setValidator(new QRegExpValidator(QRegExp("[0-9xsincotgqrpe+-=/*()^]*"), ui->userInputLine));
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
    double stepSize = ui->stepSizeEdit->text().toDouble();
    double delta = topLimit - bottomLimit;

    parseFunc(ui->userInputLine->text());


    //    MethodSimpson::solve(func, stepSize, (topLimit - bottomLimit)/stepSize, bottomLimit, topLimit);

    //    if (ui->stepTypeBox->currentIndex() == 0)
    //    {
    //        for (int i = 0; i <= stepSize ; i++)
    //        {
    //            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    //            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
    //            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number((i) * (delta / stepSize))));
    //            ui->tableWidget->setItem(i, 2, new QTableWidgetItem("yi"));
    //        }
    //    }
    //    else
    //    {
    //        int counter = 0;

    //        while (bottomLimit <= topLimit)
    //        {
    //            ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    //            ui->tableWidget->setItem(counter, 0, new QTableWidgetItem(QString::number(counter)));
    //            ui->tableWidget->setItem(counter, 1, new QTableWidgetItem(QString::number(bottomLimit)));
    //            ui->tableWidget->setItem(counter, 2, new QTableWidgetItem("yi"));

    //            counter++;
    //            bottomLimit+=stepSize;
    //        }
    //    }
    //    ui->resultTextBrowser->setText("Решение с помощью " + ui->integrationMethodBox->currentText() + "...");
}

void MainWindow::parseFunc(QString input)
{
    QList<QChar> lettersList = {'s', 'i', 'n', 'c', 'o', 't', 'g', 'q', 'r'};
    QList<QString> funcExpressions;
    size_t digitCounter = 0;
    QString buffDigits = "";
    QString buffExpressions = "";

    QMap<int, int> bracketPairIndexes;

    int x = 1;

//    funcExpressions.append("b");

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
    qDebug() << "FUNCT EXPRESSIONS = " << funcExpressions;

    for (int i = 0; i < funcExpressions.length(); i++)
    {
        if (funcExpressions[i] == "(" && !lettersList.contains(funcExpressions[i - 1][0]))
        {
            qDebug() << funcExpressions[i] << funcExpressions[i - 1];

//            bracketPairIndexes[i] = 0;

            for (int j = i; j < funcExpressions.length(); j++)
            {
                if (funcExpressions[j] == ")")
                {
                    bracketPairIndexes[i] = j;
                }
            }
        }
    }


    qDebug() << "BARCKET PAIR INDEXES " << bracketPairIndexes;

}
