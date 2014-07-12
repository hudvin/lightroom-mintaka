#ifndef KEYWORDSLOADER_H
#define KEYWORDSLOADER_H

#include <QList>
#include <QString>

#define KEYWORDS_FILE_LOCATION "C:/dev/projects/lr-plugin/lr-qt/data/keywords.txt"




class KeywordsLoader
{
public:
    KeywordsLoader();
    ~KeywordsLoader();
    QList<QString> load();
};

#endif // KEYWORDSLOADER_H
