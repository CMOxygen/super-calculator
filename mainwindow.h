#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "methodsimpson.h"

#include <QMainWindow>

#include <QRegExpValidator>
#include <QRegExp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int testFunc(){return 3;}

    void parseFunc(QString input);

private slots:
    void on_solveButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
