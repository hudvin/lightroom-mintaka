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
    QSqlQuery query("PRAGMA foreign_keys = ON;",db);
    query.exec();
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
    QSqlQuery query("SELECT id,uuid, filename FROM photos " \
                    "WHERE id NOT IN (SELECT photo_id FROM photos_tags)", db);
    QList<PhotoEntry> data;
    while (query.next()) {
        int id = query.value(0).toInt();
            QString uuid = query.value(1).toString();
            QString filename = query.value(2).toString();
            data<<PhotoEntry(id,uuid, filename);
    }
    return data;
}


QList<Keyword> DBWrapper::getKeywordsForPhoto(PhotoEntry entry){
    QList<Keyword> data;
    QSqlQuery query("SELECT tags.id, tags.tag from tags " \
                    "INNER JOIN photos_tags on tags.id = photos_tags.tag_id "
                    "INNER JOIN photos on photos.id = photos_tags.photo_id "
                    "WHERE photos.uuid=?", db);
    query.bindValue(0,entry.uuid);
    query.exec();
    while (query.next()) {
        int id = query.value(0).toInt();
        QString tag = query.value(1).toString();
        Keyword keyword(id, tag);
        data<<keyword;
     }
    return data;
}


QList<PhotoEntry> DBWrapper::getPhotosByKeyword(QString keywordValue){
    qDebug()<<"kvalue "<<keywordValue;
    QList<PhotoEntry> data;
    QSqlQuery query("SELECT p.id, p.filename, p.uuid, t.tag FROM  tags t, photos p, photos_tags "\
                    "WHERE t.tag  LIKE ? " \
                    "AND t.id=photos_tags.tag_id AND p.id = photos_tags.photo_id;", db);
    query.bindValue(0,keywordValue); //use id?
    query.exec();
    qDebug()<<query.size();
    while (query.next()) {
        int id = query.value(0).toInt();
        QString filename = query.value(1).toString();
        QString uuid = query.value(2).toString();
        PhotoEntry photoEntry(id, uuid,filename);
        data<<photoEntry;
     }
    return data;
}


QSqlQueryModel* DBWrapper::getTagsTableModel(){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT tag, (SELECT COUNT(*) FROM photos_tags "\
                    "WHERE photos_tags.tag_id=tags.id ) as num " \
                    "FROM tags WHERE is_hidden=0 " \
                    "UNION " \
                    " SELECT '[without tags]', " \
                    "(SELECT COUNT(*) FROM photos " \
                    "WHERE photos.id NOT IN(SELECT photos_tags.photo_id FROM photos_tags)) as num "
                    );

    model->setHeaderData(0,Qt::Horizontal, "keyword");
    model->setHeaderData(1,Qt::Horizontal, "number of \n photos");
    return model;
}


