#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "methodsimpson.h"
#include "methodtrapezoid.h"
#include "methodsquares.h"

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

private slots:
    void on_solveButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
