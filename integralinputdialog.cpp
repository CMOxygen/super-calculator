#include "integralinputdialog.h"
#include "ui_integralinputdialog.h"

IntegralInputDialog::IntegralInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntegralInputDialog)
{
    ui->setupUi(this);
}

IntegralInputDialog::~IntegralInputDialog()
{
    delete ui;
}
