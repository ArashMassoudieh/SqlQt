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
};

QString singleqstringwcommas(QStringList &S);

#endif // SQLOPS_H
