#include "dlgaddnotes.h"
#include "ui_dlgaddnotes.h"
#include "sqlops.h"
#include "qstringlist.h"
#include "qdebug.h"

DlgAddNotes::DlgAddNotes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddNotes)
{
    ui->setupUi(this);
    SqlOps sqlop;
    QStringList field; field.append("Last_Name"); field.append("First_Name");
    QStringList names = sqlop.getcolumn(field,"Students");
    ui->comboBox->addItems(names);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(onOkClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

DlgAddNotes::~DlgAddNotes()
{
    delete ui;
}

void DlgAddNotes::onOkClicked()
{
    SqlOps sqlop;
    qDebug()<< ui->comboBox->currentText();
    QString std_id = sqlop.getstudentID(ui->comboBox->currentText());
    qDebug()<<std_id;
    QString Sqltext = "INSERT INTO Notes (STUDENT_ID,Date,NOTE) VALUES('" + std_id + "',NOW(),'" + ui->plainTextEdit->toPlainText() +"')";
    qDebug()<<Sqltext;
    QSqlQuery qry;
    qry.prepare(Sqltext);
    if (!qry.exec())
    {
        qDebug()<<qry.lastError();
    }
}
