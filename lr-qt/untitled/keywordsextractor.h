#ifndef KEYWORDSEXTRACTOR_H
#define KEYWORDSEXTRACTOR_H

#include <QSharedPointer>
#include <QList>
#include <QPair>
#include <QString>
#include <QWidget>
#include <keywordsextractorstrategy.h>




class KeywordsExtractor : public QObject{
      Q_OBJECT
public:

    explicit KeywordsExtractor( QSharedPointer<KeywordsExtractorStrategy> extractorStrategy,
                                QWidget *parent = 0);
    void addPhotoEntries(QList<PhotoEntry> photos);
    int getTotalCount();
    int getProcessedCount();
    bool isFinished();
    void startExtraction();
    QList<QPair<PhotoEntry, QList<Keyword>>> getResults();


private:
   QSharedPointer<KeywordsExtractorStrategy> extractorStrategy;
   QList<PhotoEntry> photos;
   QList<QPair<PhotoEntry, QList<Keyword>>> result;
   volatile bool canWork = true;
public slots:
   void stop();

private slots:
   void process();

signals:
    void finished();
    void error(QString err);
    void valueChanged(const int i);

};

#endif // KEYWORDSEXTRACTOR_H
