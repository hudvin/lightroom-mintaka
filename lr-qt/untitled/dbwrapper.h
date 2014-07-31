#ifndef DBWRAPPER_H
#define DBWRAPPER_H

#include <QtSql/QtSql>
#include <QList>
#include <QString>

#include <csvreader.h>
#include <structures.h>


class DBWrapper
{
public:
    static DBWrapper &GetInstance(){
          static DBWrapper instance;
          return instance;
     }

    ~DBWrapper();
    void addPhotoEntry(PhotoEntry entry);
    Keyword getKeywordByValue(QString value);
    PhotoEntry getPhotoByUUID(QString uuid);
    void addKeyword(PhotoEntry photo, Keyword keyword);
    QList<PhotoEntry> getPhotosWithoutTags();
    QList<PhotoEntry> getPhotosByKeyword(QString keywordValue="%");
    QList<PhotoEntry> getAllPhotos();
    QSqlDatabase getDatabase();
    void deleteAllData();
    void closeDatabase();
    QSqlQueryModel* getTagsTableModel();
    QList<Keyword> getKeywordsForPhoto(PhotoEntry entry);
private:
    DBWrapper();
    QSqlDatabase db;

};

#endif // DBWRAPPER_H
