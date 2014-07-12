#include "dbwrapper.h"
#include <QtSql/QtSql>
#include <QtDebug>
#include <QString>
#include <QDir>
#include <QList>



DBWrapper::DBWrapper(){
    db = (QSqlDatabase::addDatabase("QSQLITE"));
    QString path("C:/dev/projects/lr-plugin/lr-qt/data");
    path.append(QDir::separator()).append("plugin.origin.db");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    db.open();
    qDebug()<<path<<db.lastError();

}

DBWrapper::~DBWrapper(){
  qDebug()<<"before close database";
  qDebug()<<db.isOpen();
  if(db.isOpen()){
      db.close();
  }
  qDebug()<<"close database";
}

QList<Tag> DBWrapper::getVisibleTags(){
   QSqlQuery query("SELECT id, tag FROM tags WHERE is_hidden=0", db);
   QList<Tag> data;
   while (query.next()) {
           int id = query.value(0).toInt();
           QString tag = query.value(1).toString();
           data<<Tag(id, tag);
           qDebug() << tag << id;
   }
   return data;
}
