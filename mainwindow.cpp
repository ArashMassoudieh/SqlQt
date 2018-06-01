#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <sqlops.h>
#include "sqldialog.h"
#include <QTextEdit>
#include <QInputDialog>
#include "form.h"
#include "formdialog.h"
#include "qsqlrecord.h"
#include "qsqlfield.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionImport_CSV, SIGNAL(triggered()), this, SLOT(openCSV()));
    connect(ui->actionSql_Commands, SIGNAL(triggered()), this, SLOT(OnSqlCommandsAction()));
    connect(ui->actionAdd_Row, SIGNAL(triggered()), this, SLOT(OnAddRow()));
    QStringList tables = getdb()->tables();
    qDebug()<<tables;
    for (int i=0; i<tables.size(); i++)
    {
        QAction *actionTables = new QAction(this);
        actionTables->setText(tables[i]);
        actionTables->setObjectName(tables[i]);
        connect(actionTables,SIGNAL(triggered()),this, SLOT(OnSelectTable()));
        ui->menuSelect_Table->addAction(actionTables);
    }
}

MainWindow::~MainWindow()
{
    dbconnect.close();
    delete ui;
}

void MainWindow::openCSV()
{

    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
                                                      "/home",
                                                      ("CSV files (*.csv *.txt)"));

    QString TableName = QInputDialog::getText(this, "Table Name",
                "Table Name");
    SqlOps SOps;
    SOps.ConvertCSVtoTable(fileName,TableName);

}

void MainWindow::OnSqlCommandsAction()
{
    SqlDialog* sqldialog = new SqlDialog(this);
    sqldialog->show();
}

void MainWindow::OnAddRow()
{
    Form* formaddrow = new Form(this);
    QList<cField> Fields;
    //cField fld1("name","string","arash");
    //cField fld2("lastname","string","massoudieh");
    //cField fld3("age","int","34");
    //Fields<<fld1<<fld2<<fld3;
    QSqlRecord record = getdb()->record(selected_table);
    for (int i=0; i<record.count(); i++)
    {
        qDebug()<<record.field(i).name()<<record.field(i).typeID();
        cField fld(record.field(i).name(),record.field(i).typeID(),QString::number(record.field(i).length()));
        Fields<<fld;
    }
    formaddrow->setup(&Fields);
    FormDialog* frmdlg = new FormDialog(this,formaddrow);
    frmdlg->show();
}

QDockWidget* MainWindow::dock(int i)
{
    if (i==1)
        return ui->dockWidget;
    else if (i==2)
        return ui->dockWidget_2;
    else if (i==3)
        return ui->dockWidget_3;

    return nullptr;
}

void MainWindow::status_write(QString s)
{
    ui->label->setText(s);
}

void MainWindow::OnSelectTable()
{
    qDebug()<<"here";
    QAction* pAction = qobject_cast<QAction*>(sender());
    Q_ASSERT(pAction);
    selected_table = pAction->text();

}

QList<cField> getfieldsfromselectedtable()
{

}
