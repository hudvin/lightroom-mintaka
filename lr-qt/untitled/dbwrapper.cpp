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
  qDebug()<<"call destructor of DBWrapper";
}

void DBWrapper::closeDatabase(){
    qDebug()<<"before close database";
    qDebug()<<db.isOpen();
    if(db.isOpen()){
        db.close();
    }
    qDebug()<<"close database";
}

QSqlDatabase DBWrapper::getDatabase(){
    return db;
}


QList<Keyword> DBWrapper::getVisibleKeywords(){
   QSqlQuery query("SELECT id, Keyword FROM Keywords WHERE is_hidden=0", db);
   QList<Keyword> data;
   while (query.next()) {
           int id = query.value(0).toInt();
           QString keyword = query.value(1).toString();
           data<<Keyword(id, keyword);
           qDebug() << keyword << id;
   }
   return data;
}


void DBWrapper::deleteAllData(){
    QSqlQuery query;
    query.exec("DELETE FROM photo_Keywords");
    query.exec("DELETE FROM photos");
}

void DBWrapper::addPhotoEntry(PhotoEntry entry){
    QSqlQuery query;
    bool  ret = query.exec(QString("insert into photos(uuid, filename) values('%1','%2')")
           .arg(entry.uuid).arg(entry.filename));
    qDebug()<<ret;
}


QList<PhotoEntry> DBWrapper::getPhotos(){
    QSqlQuery query("SELECT uuid, filename FROM photos", db);
    QList<PhotoEntry> data;
    while (query.next()) {
            QString uuid = query.value(0).toString();
            QString filename = query.value(1).toString();
            data<<PhotoEntry(uuid, filename);
    }
    return data;
}
