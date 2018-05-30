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

class cField
{
public:
    cField(QString s1, QString s2=QString(), QString s3 = QString(), QString s4 = QString());
    cField();
    QString name;
    QString type;
    QString defaultval;
    QString val;
};

QString singleqstringwcommas(QStringList &S, bool );

#endif // SQLOPS_H
