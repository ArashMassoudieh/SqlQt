#include "sqldialog.h"
#include "ui_sqldialog.h"
#include <QTableView>
#include <QSqlQueryModel>
#include <mainwindow.h>
#include <qdebug.h>
#include <qdockwidget.h>
#include <QKeyEvent>
#include <algorithm>

SqlDialog::SqlDialog(MainWindow *_parent) :
    QDialog(_parent),
    ui(new Ui::SqlDialog)
{
    parent = _parent;
    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(returnPressed()),this,SLOT(SqlCommadEntered()));
    ui->lineEdit->installEventFilter(this);
}

SqlDialog::~SqlDialog()
{
    delete ui;
}

bool SqlDialog::eventFilter(QObject* obj, QEvent *event)
{
    if (obj == ui->lineEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Up)
            {
                 qDebug() << "lineEdit -> Qt::Key_Up";
                 whereonlist = std::max(whereonlist-1,0);
                 ui->lineEdit->setText(commands[whereonlist]);
                 return true;
            }
            else if(keyEvent->key() == Qt::Key_Down)
            {
                qDebug() << "lineEdit -> Qt::Key_Down";
                whereonlist = std::min(whereonlist+1,commands.size()-1);
                ui->lineEdit->setText(commands[whereonlist]);
                return true;
            }
        }
        return false;
    }
    return SqlDialog::eventFilter(obj, event);
}

void SqlDialog::SqlCommadEntered()
{
    QSqlQuery qry;
    commands.append(ui->lineEdit->text());
    qry.prepare(ui->lineEdit->text());
    if( !qry.exec() )
    {   qDebug() << qry.lastError();
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append(ui->lineEdit->text());
        ui->textBrowser->append("SQL error: ");
        ui->textBrowser->append(qry.lastError().text());
        ui->textBrowser->setTextColor(Qt::black);
        parent->status_write(qry.lastError().text());
    }
    else
    {   qDebug() << "Ok!";
        ui->textBrowser->append(ui->lineEdit->text());
        ui->textBrowser->append("Ok!");
        parent->status_write("Ok!");
        if (ui->lineEdit->text().toLower().contains("select"))
        {
            QSqlQueryModel *model = new QSqlQueryModel(this);
            model->setQuery(qry);

            QTableView *view = new QTableView;
            view->setModel(model);
            view->resizeColumnsToContents();
            parent->dock(2)->setWidget(view);
            view->show();
        }
    }
    ui->lineEdit->clear();
    whereonlist = commands.size();
}


