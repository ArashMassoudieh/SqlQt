#include "connectmysql.h"

#include <qdebug.h>
connectmysql::connectmysql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("test.cghsjfqfipfe.us-west-2.rds.amazonaws.com");
    db.setUserName("arash");
    db.setPassword("8091921.z.Z");
    db.setDatabaseName("CEE_Data");
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
