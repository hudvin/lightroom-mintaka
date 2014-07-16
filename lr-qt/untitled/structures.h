#include <QString>

#ifndef STRUCTURES_H
#define STRUCTURES_H


struct PhotoEntry{
    PhotoEntry(QString uuid, QString filename){
        this->filename = filename;
        this->uuid = uuid;
    }

    QString uuid, filename;
};

struct Keyword{
    Keyword(int id, QString keyword){
        this->id = id;
        this->keyword = keyword;
    }
    int id;
    QString keyword;
};


#endif // STRUCTURES_H
