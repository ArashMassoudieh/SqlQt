#include "sqlops.h"
#include <QDebug>
#include <QStringList>

SqlOps::SqlOps()
{

}

bool SqlOps::ConvertCSVtoTable(QString csvfilename, QString tablename)
{
    QFile file(csvfilename);
    if(!file.open(QFile::ReadOnly |
                      QFile::Text))
        {
            qDebug() << " Could not open file for writing";
            return false;
        }
    QTextStream in(&file);
    QStringList header = in.readLine().split(",");
    QSqlQuery qry;
    QString s = "CREATE TABLE IF NOT EXISTS " + tablename + "(";
    s += header[0] + " VARCHAR(30)";
    for (int i=1; i<header.size(); i++) {
        s += "," + header[i] + " VARCHAR(30)";
    }
    s+=")";
    qry.prepare(s);
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug() << "Table created!";

    while (!in.atEnd())
    {   QStringList row = in.readLine().split(",");
        qDebug() << row;
        QString s = "INSERT INTO " + tablename + " (";
        s+=singleqstringwcommas(header);
        s+=") VALUES (" + singleqstringwcommas(row) + ")";

        qry.prepare(s);
        if( !qry.exec() )
          qDebug() << qry.lastError();
        else
          qDebug( "Inserted!" );
    }
    file.close();
    return true;
}

QString singleqstringwcommas(QStringList &S)
{
    if (!S.size()) return QString();
    QString s=S[0];
    for (int i=1;i<S.size(); i++){s+=","+S[i];}
    return s;

}
