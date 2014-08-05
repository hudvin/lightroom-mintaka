#include "keywordsextractor.h"
#include <QThread>
#include <QTimer>

KeywordsExtractor::KeywordsExtractor(QSharedPointer<KeywordsExtractorStrategy> extractorStrategy,
                                     QWidget *parent) : QObject(parent){
    this->extractorStrategy = extractorStrategy;
}

void KeywordsExtractor::addPhotoEntries(QList<PhotoEntry> photos){
    this->photos = photos;
}

QList<QPair<PhotoEntry, QList<Keyword>>> KeywordsExtractor::getResults(){
    return result;
}


int KeywordsExtractor::getTotalCount(){
    return this->photos.size();
}
int KeywordsExtractor::getProcessedCount(){
    return this->result.size();
}
bool KeywordsExtractor::isFinished(){
    return result.size()<photos.size();
}

void KeywordsExtractor::stop(){
    qDebug()<<"stop request";
    canWork = false;
}


void KeywordsExtractor::startExtraction(){
    QThread* thread = new QThread;
    moveToThread(thread);
  //  connect(this, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), this, SLOT(process()));
   // connect(this, SIGNAL(finished()), thread, SLOT(quit()));
  //  connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
  //  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void KeywordsExtractor::process(){
    foreach (PhotoEntry photoEntry, photos) {
       qDebug()<<canWork;
        if(!canWork){
           break;
       }
       QList<Keyword> keywords =
               extractorStrategy.data()->extract(photoEntry);
       result.append(QPair<PhotoEntry, QList<Keyword>>(photoEntry, keywords));
       qDebug()<<"processed "<<getProcessedCount();
       QThread::currentThread()->msleep(200);
       emit valueChanged(getProcessedCount());
    }
    emit finished();
}
