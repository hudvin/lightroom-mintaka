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
    QList<Keyword> getVisibleKeywords();
    void addPhotoEntry(PhotoEntry entry);
    Keyword getKeywordByValue(QString value);
    PhotoEntry getPhotoByUUID(QString uuid);
    void addKeyword(PhotoEntry photo, Keyword keyword);
    QList<PhotoEntry> getPhotos();
    QSqlDatabase getDatabase();
    void deleteAllData();
    void closeDatabase();
private:
    QSqlDatabase db;

};

#endif // DBWRAPPER_H
