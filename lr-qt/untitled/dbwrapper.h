#ifndef DBWRAPPER_H
#define DBWRAPPER_H

#include <QtSql/QtSql>
#include <QList>
#include <QString>

struct Tag{
    Tag(int id, QString tag){
        this->id = id;
        this->tag = tag;
    }

    int id;
    QString tag;

};


class DBWrapper
{
public:
    DBWrapper();
    ~DBWrapper();
    QList<Tag> getVisibleTags();

private:
    QSqlDatabase db;

};

#endif // DBWRAPPER_H
