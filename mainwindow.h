#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectmysql.h"
#include "sqlops.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDockWidget* dock(int i);
    void status_write(QString s);
    QSqlDatabase *getdb() {return dbconnect.getdb();};
    QString selected_table;
    QList<cField> getfieldsfromselectedtable();
public slots:
    void openCSV();
    void OnSqlCommandsAction();
    void OnAddNotesAction();
    void OnAddRow();
    void OnSelectTable();
    void OnSelectQuery();


private:
    Ui::MainWindow *ui;
    connectmysql dbconnect;
};

#endif // MAINWINDOW_H
