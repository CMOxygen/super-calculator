#ifndef INTEGRALINPUTDIALOG_H
#define INTEGRALINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class IntegralInputDialog;
}

class IntegralInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IntegralInputDialog(QWidget *parent = nullptr);
    ~IntegralInputDialog();

private:
    Ui::IntegralInputDialog *ui;
};

#endif // INTEGRALINPUTDIALOG_H
