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
    DBWrapper();
    ~DBWrapper();
    void addPhotoEntry(PhotoEntry entry);
    Keyword getKeywordByValue(QString value);
    PhotoEntry getPhotoByUUID(QString uuid);
    void addKeyword(PhotoEntry photo, Keyword keyword);
    QList<PhotoEntry> getPhotosWithoutTags();
    QList<PhotoEntry> getPhotosByKeyword(QString keywordValue="%");
    QList<PhotoEntry> DBWrapper::getAllPhotos();
    QSqlDatabase getDatabase();
    void deleteAllData();
    void closeDatabase();
    QSqlQueryModel* getTagsTableModel();
    QList<Keyword> getKeywordsForPhoto(PhotoEntry entry);
private:
    QSqlDatabase db;

};

#endif // DBWRAPPER_H
