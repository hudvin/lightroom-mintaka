#ifndef KEYWORDSEXTRACTORSTRATEGY_H
#define KEYWORDSEXTRACTORSTRATEGY_H

#include <QList>
#include <QDebug>
#include <QtGlobal>
#include <QString>

#include <structures.h>
#include <constants.h>


class KeywordsExtractorStrategy{

public:
    KeywordsExtractorStrategy() {}
    ~KeywordsExtractorStrategy(void) {qDebug()<<"remove strategy object";}
    virtual QList<Keyword> extract(PhotoEntry photoEntry) = 0;

};


class RandomKeywordsExtractorStrategy : public KeywordsExtractorStrategy {
public:

    RandomKeywordsExtractorStrategy(QList<Keyword> allKeywords){
        this->allKeywords = allKeywords;
    }

    virtual  QList<Keyword> extract(PhotoEntry photoEntry){
        QList<Keyword> keywords;
//        QList<QString> defaultKeywords = Constants::Keywords::DEFAULT_KEYWORDS;
        int numOfKeywords = randInt(1,3);
        while(keywords.size()<numOfKeywords){
            int index = randInt(0,allKeywords.size()-1);
            Keyword keyword = allKeywords.at(index);
            if(!keywords.contains(keyword)){
                keywords+=keyword;
                qDebug()<<"strategy: "<< photoEntry.filename<<"::"<<keyword.keyword;
            }

        }
        return keywords;
    }


private:

 QList<Keyword> allKeywords;

 int randInt(int low, int high){
        return qrand() % ((high + 1) - low) + low;
  }

};


#endif // KEYWORDSEXTRACTORSTRATEGY_H
