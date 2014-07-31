#include <QDebug>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QMenu>
#include <QAction>

#include "imagelistwidget.h"
#include "constants.h"


ImageListWidget::ImageListWidget(QWidget *parent) :
    QListWidget(parent){
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
             SLOT(showContextMenuForWidget(const QPoint &)));
}


void ImageListWidget::setCurrentKeyword(QString currentKeyword){
    this->currentKeyword = currentKeyword;
}

QString ImageListWidget::getCurrentKeyword(){
    return this->currentKeyword;
}


void ImageListWidget::showContextMenuForWidget(const QPoint &pos){
    if(!(currentKeyword==Constants::Keywords::ALL_PHOTOS
         || currentKeyword==Constants::Keywords::WITHOUT_KEYWORDS)){
        QMenu contextMenu("Context menu", this);
        QModelIndex modelIndex = this->indexAt(pos);
        if(modelIndex.isValid()){
            QString uuid = modelIndex.data(Constants::MagicNumbers::DATA_KEY).toString();
            QAction removeAction("Remove", this);
            QAction removeAllAction("Remove all",this);
            contextMenu.addAction(&removeAction);
            contextMenu.addAction(&removeAllAction);
            QAction* exec = contextMenu.exec(mapToGlobal(pos));
            if(exec == &removeAction){
                dbWrapper->removeKeywordFromPhoto(dbWrapper->getPhotoByUUID(uuid), dbWrapper->getKeywordByValue(currentKeyword));
                emit pleaseReload();
            }else if(exec == &removeAllAction){
                PhotoEntry photoEntry = dbWrapper->getPhotoByUUID(uuid);
                QList<Keyword> keywords = dbWrapper->getKeywordsForPhoto(photoEntry);
                foreach (Keyword keyword, keywords) {
                   dbWrapper->removeKeywordFromPhoto(photoEntry, keyword);
                }
                emit pleaseReload();
            }
        }
    }
}

void ImageListWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        dragStartPosition = event->pos();
    }
}

void ImageListWidget::mouseMoveEvent(QMouseEvent *event){
    if (!(event->buttons() & Qt::LeftButton))
               return;
           if ((event->pos() - dragStartPosition).manhattanLength()
                < QApplication::startDragDistance())
               return;

           QDrag *drag = new QDrag(this);
           QMimeData *mimeData = new QMimeData;
           QString uuid = indexAt(event->pos()).data(Constants::MagicNumbers::DATA_KEY).toString();
           mimeData->setText(uuid);
           drag->setMimeData(mimeData);
           drag->start(Qt::CopyAction | Qt::MoveAction);
}

