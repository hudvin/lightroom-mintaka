#include "csvreader.h"

#include <pathutils.h>

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QStringList>


CSVReader::CSVReader(){
}

void CSVReader::load(){
    //QList<Entry> entries;
    QString path = PathUtils::getAppTmpDir()+"/"+ENTRIES_FILE_NAME;
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while ( !in.atEnd() ){
            QStringList tokens = in.readLine().split(",");
            PhotoEntry entry(tokens[0], tokens[1]);
            entries<<entry;
            qDebug()<<tokens;
        }
        inputFile.close();
    }
}

bool CSVReader::isUUIDInList(QString uuid){
    foreach(PhotoEntry entry, entries){
        if(entry.uuid==uuid){
            return true;
        }
    }
    return false;
}

QList<PhotoEntry> CSVReader::getEntries(){
    return entries;
}
