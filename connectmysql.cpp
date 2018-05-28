#include "connectmysql.h"

#include <qdebug.h>
connectmysql::connectmysql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.12");
    db.setUserName("arash");
    db.setPassword("8091921.z.Z");
    db.setDatabaseName("db_name");
    if( !db.open() )
      {
        qDebug() << db.lastError();
        qFatal( "Failed to connect." );
      }

      qDebug( "Connected!" );

}

void connectmysql::close()
{
    db.close();
}
