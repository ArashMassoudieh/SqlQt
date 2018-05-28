#ifndef SQLDIALOG_H
#define SQLDIALOG_H

#include <QDialog>
#include "sqlops.h"
#include <QSqlQuery>

class MainWindow;

namespace Ui {
class SqlDialog;
}

class SqlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SqlDialog(MainWindow *parent = 0);
    ~SqlDialog();
    MainWindow *parent;
    int whereonlist=0;
    bool eventFilter(QObject* obj, QEvent *event);

private slots:
    void SqlCommadEntered();


private:
    Ui::SqlDialog *ui;
    SqlOps sqlops;
    QStringList commands;
};

#endif // SQLDIALOG_H
