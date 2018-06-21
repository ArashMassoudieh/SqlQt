#include "mainwindow.h"
#include <QApplication>
//#include <sql.h>
#include <qsqldatabase.h>
#include <qdebug.h>
#include <qsqlerror.h>
#include <qsqlrecord.h>
#include <qsqlquery.h>
#include <connectmysql.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

    return a.exec();

}
