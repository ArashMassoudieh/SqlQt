#include "formdialog.h"
#include "ui_formdialog.h"

FormDialog::FormDialog(QWidget *parent, Form* _form) :
    QDialog(parent),
    ui(new Ui::FormDialog)
{
    ui->setupUi(this);
    setform(_form);
}

FormDialog::~FormDialog()
{
    delete ui;
}

void FormDialog::setform(Form* _form)
{
    form = _form;
    ui->horizontalLayout->addWidget(form);
}
