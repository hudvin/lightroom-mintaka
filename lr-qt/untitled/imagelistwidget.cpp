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
            QString uuid = modelIndex.data(5).toString();
            qDebug()<< uuid;
            QAction removeAction("Remove", this);
            contextMenu.addAction(&removeAction);
            if(contextMenu.exec(mapToGlobal(pos)) == &removeAction){
                dbWrapper->removeKeywordFromPhoto(dbWrapper->getPhotoByUUID(uuid), dbWrapper->getKeywordByValue(currentKeyword));
                qDebug()<<"remove action has been called";
                emit itemWasRemoved();
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
           QString uuid = indexAt(event->pos()).data(5).toString();//FIXME Magic Number
           mimeData->setText(uuid);
           drag->setMimeData(mimeData);
           //get info about current selection - pass instead of Some text
           Qt::DropAction dropAction = drag->start(Qt::CopyAction | Qt::MoveAction);


}

