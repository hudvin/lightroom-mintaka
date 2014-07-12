#include "keywordsloader.h"
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QList>

KeywordsLoader::KeywordsLoader(){
}

KeywordsLoader::~KeywordsLoader(){
    qDebug()<<"destroy";
}

QList<QString> KeywordsLoader::load(){
    qDebug()<<KEYWORDS_FILE_LOCATION<<endl;
    QList<QString> keywords;
    QFile inputFile(KEYWORDS_FILE_LOCATION);
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while ( !in.atEnd() ){
            QString line = in.readLine();
            keywords<<line;
            qDebug()<<line;
        }
        inputFile.close();
    }
    return keywords;
}
