#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <sqlops.h>
#include "sqldialog.h"
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionImport_CSV, SIGNAL(triggered()), this, SLOT(openCSV()));
    connect(ui->actionSql_Commands, SIGNAL(triggered()), this, SLOT(OnSqlCommandsAction()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openCSV()
{
    qDebug()<<"here!";
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
                                                      "/home",
                                                      ("CSV files (*.csv *.txt)"));
    SqlOps SOps;
    SOps.ConvertCSVtoTable(fileName,"test");

}

void MainWindow::OnSqlCommandsAction()
{
    SqlDialog* sqldialog = new SqlDialog(this);
    sqldialog->show();
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
