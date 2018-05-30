#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::setup(QList<cField> *_Fields)
{
    Fields = _Fields;

    for (int i=0; i<Fields->size(); i++)
    {
        QLabel *lbl = new QLabel(this);
        lbl->setObjectName(QStringLiteral("Label")+QString::number(i));
        lbl->setText((*Fields)[i].name);
        Label.append(lbl);
        ui->formLayout->setWidget(i, QFormLayout::LabelRole, lbl);
        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdit->setObjectName(QStringLiteral("lineEdit")+QString::number(i));
        Line_Edit.append(lineEdit);
        ui->formLayout->setWidget(i, QFormLayout::FieldRole, lineEdit);
    }
}
