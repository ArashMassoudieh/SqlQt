#ifndef CONNECTMYSQL_H
#define CONNECTMYSQL_H

#include <qsqldatabase.h>
#include <qsqlerror.h>

class connectmysql
{
public:
    connectmysql();
    void close();
private:
    QSqlDatabase db;
};

#endif // CONNECTMYSQL_H
