#ifndef SQLOPS_H
#define SQLOPS_H

#include <qfile.h>
#include <QTextStream>
#include <qsqlquery.h>
#include <qsqlerror.h>

class SqlOps
{
public:
    SqlOps();
    bool ConvertCSVtoTable(QString csvfilename, QString tablename);
    QStringList gettypesCSV(QString csvfilename);
};

QString singleqstringwcommas(QStringList &S, bool );

#endif // SQLOPS_H
