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
      //  db.close();
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

Keyword DBWrapper::getKeywordByValue(QString value){
    QSqlQuery query("SELECT id, tag FROM tags WHERE tag=? AND is_hidden=0", db);
    query.bindValue(0,value);
    query.exec();
    if(query.next()){
        int id = query.value(0).toInt();
        QString keyword = query.value(1).toString();
        Keyword data(id, keyword);
        return data;
    } else{
       return Keyword(-1,"");
    }
}

PhotoEntry DBWrapper::getPhotoByUUID(QString uuid){
    QSqlQuery query("SELECT id, uuid, filename FROM photos WHERE uuid=?", db);
    query.bindValue(0,uuid);
    query.exec();
    if(query.next()){
        int id = query.value(0).toInt();
        QString uuid = query.value(1).toString();
        QString filename = query.value(2).toString();
        PhotoEntry data(id, uuid,filename);
        return data;
    } else{
       return PhotoEntry(-1,"","");
    }
}

 void DBWrapper::addKeyword(PhotoEntry photo, Keyword keyword){
    //check if already added!!!!
    QSqlQuery query;
    bool  ret = query.exec(QString("insert into photos_tags(photo_id, tag_id) values(%1,%2)")
           .arg(photo.id).arg(keyword.id));
    qDebug()<<ret << db.lastError().text();
}

void DBWrapper::deleteAllData(){
    QSqlQuery query;
    query.exec("DELETE FROM photos_tags");
    query.exec("DELETE FROM photos");
}

void DBWrapper::addPhotoEntry(PhotoEntry entry){
    QSqlQuery query;
    bool  ret = query.exec(QString("insert into photos(uuid, filename) values('%1','%2')")
           .arg(entry.uuid).arg(entry.filename));
    qDebug()<<ret;
}


QList<PhotoEntry> DBWrapper::getPhotos(){
    QSqlQuery query("SELECT id,uuid, filename FROM photos", db);
    QList<PhotoEntry> data;
    while (query.next()) {
        int id = query.value(0).toInt();
            QString uuid = query.value(1).toString();
            QString filename = query.value(2).toString();
            data<<PhotoEntry(id,uuid, filename);
    }
    return data;
}
