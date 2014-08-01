#ifndef KEYWORDSEXTRACTORSTRATEGY_H
#define KEYWORDSEXTRACTORSTRATEGY_H

#include <QList>
#include <structures.h>
#include <QDebug>

class KeywordsExtractorStrategy{

public:
    KeywordsExtractorStrategy(void) {}
    ~KeywordsExtractorStrategy(void) {qDebug()<<"remove strategy object";}
    virtual QList<Keyword> extract(PhotoEntry photoEntry) = 0;

};


class RandomKeywordsExtractorStrategy : public KeywordsExtractorStrategy {
public:

    virtual  QList<Keyword> extract(PhotoEntry photoEntry){
        qDebug()<<"strategy: "<< photoEntry.filename;
        return QList<Keyword>();
    }


};


#endif // KEYWORDSEXTRACTORSTRATEGY_H
