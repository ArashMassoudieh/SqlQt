#include "sqlops.h"
#include <QDebug>
#include <QStringList>
#include "vector"

using namespace std;

SqlOps::SqlOps()
{

}

QStringList SqlOps::getcolumn(QString fieldname, QString tablename)
{
    QString s = "select " + fieldname + " from " + tablename;
    QStringList out;
    QSqlQuery qry;
    qry.prepare(s);

    if (!qry.exec())
    {
        qDebug()<<qry.lastError();
    }
    else
    {
        while (qry.next()) {
            out.append(qry.value(0).toString());
            qDebug()<<qry.value(0)<<endl;
            qry.next();
        }
    }
    return out;
}

QStringList SqlOps::getcolumn(QStringList fieldname, QString tablename)
{
    QString s = "select " + fieldname[0];
    for (int i=1; i<fieldname.size(); i++)
        s += "," + fieldname[i];
    s += " from " + tablename;
    QStringList out;
    QSqlQuery qry;
    qry.prepare(s);

    if (!qry.exec())
    {
        qDebug()<<qry.lastError();
    }
    else
    {
        while (qry.next()) {
            QString fullval = qry.value(0).toString();
            for (int i=1; i<fieldname.size(); i++)
            {
                fullval += ", " + qry.value(i).toString();
            }
            out.append(fullval);
            qry.next();
        }
    }
    return out;
}

QString SqlOps::getstudentID(QString fullname)
{
    qDebug()<<fullname;
    if (fullname.split(",").size()<2) return "";
    QString first_name = fullname.split(",")[1].trimmed();
    QString last_name = fullname.split(",")[0].trimmed();
    QString s = "select * from Students where TRIM(First_Name) = '" + first_name +"' AND TRIM(Last_name) = '" + last_name + "'";
    qDebug()<<s;
    QSqlQuery qry;
    qry.prepare(s);
    QString ID;
    if (!qry.exec())
    {
        qDebug()<<qry.lastError();
    }
    else
    {   qry.next();
        ID = qry.value("EMPL_ID") .toString();
    }
    return ID;
}

QStringList SqlOps::gettypesCSV(QString csvfilename)
{
    vector<QString> types;
    vector<int> sizes;
    QStringList out;
    QFile file(csvfilename);
    if(!file.open(QFile::ReadOnly |
                      QFile::Text))
        {
            qDebug() << " Could not open file for writing";
            return out;
        }
    QTextStream in(&file);
    QStringList header = in.readLine().split(",");

    types.resize(header.size());
    sizes.resize(header.size());


    while (!in.atEnd())
    {   QStringList row = in.readLine().split(",");
        for (int i=0; i<header.size(); i++)
        {   if (row[i].toDouble() == row[i].toInt() && row[i].toDouble()!=0 )
            {
                if (types[i]!="double" && types[i]!="string") types[i]="int";
            }
            else if (row[i].toDouble() != row[i].toInt() && row[i].toDouble()!=0 )
            {
                if (types[i]!="string") types[i]="double";
            }
            else
            {   types[i]="string";
                sizes[i]=row[i].size();
            }
        }
    }
    for (int i=0; i<header.size(); i++)
    {   if (types[i].contains("double"))
            out<<"DOUBLE";
        else if (types[i] == "int")
            out<<"INT";
        else
            out<<"VARCHAR(" + QString::number(sizes[i]+10) + ")";

    }
    file.close();
    return out;

}

bool SqlOps::ConvertCSVtoTable(QString csvfilename, QString tablename)
{
    QStringList types = gettypesCSV(csvfilename);
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
    s += header[0] +" " + types[0];
    for (int i=1; i<header.size(); i++) {
        s += "," + header[i] + " " + types[i];
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
        s+=singleqstringwcommas(header, false);
        s+=") VALUES (" + singleqstringwcommas(row,true) + ")";

        qry.prepare(s);
        if( !qry.exec() )
        {   qDebug() << s;
            qDebug() << qry.lastError();

        }
        else
          qDebug( "Inserted!" );
    }
    file.close();
    return true;
}

QString singleqstringwcommas(QStringList &S, bool single_quotation=false)
{

    QString qt;
    if (single_quotation) qt = "'";
    if (!S.size()) return QString();

    QString s=qt + S[0] + qt;
    for (int i=1;i<S.size(); i++){s+="," + qt +S[i].trimmed() + qt;}
    return s.replace("\"","");

}

cField::cField(QString _name, QString _type, QString _default_val, QString _val)
{
    name = _name;
    type = _type;
    defaultval = _default_val;
    val = _val;
}

cField::cField(QString s1, int typeID, QString s3, QString s4)
{
    name = s1;
    if (typeID == 3)
        type = "int";
    else if (typeID == 253)
        type = "string";
    defaultval = s3;
    val = s4;
}

cField::cField()
{

}
