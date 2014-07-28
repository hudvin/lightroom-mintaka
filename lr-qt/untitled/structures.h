#include <QString>

#ifndef STRUCTURES_H
#define STRUCTURES_H


struct PhotoEntry{
    PhotoEntry(int id,QString uuid, QString filename){
        this->id = id;
        this->filename = filename;
        this->uuid = uuid;
    }

    int id;
    QString uuid, filename;
};

struct Keyword{
    Keyword(int id, QString keyword){
        this->id = id;
        this->keyword = keyword;
    }
    int id;
    QString keyword;
    bool operator==(const Keyword& other)const{
        if(this->keyword==(other.keyword)){
            return true;
        }
        return false;
    }
};


#endif // STRUCTURES_H
