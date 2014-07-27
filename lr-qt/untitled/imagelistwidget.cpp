#include "imagelistwidget.h"
#include <QDebug>
#include <QApplication>
#include <QMimeData>
#include <QDrag>

ImageListWidget::ImageListWidget(QWidget *parent) :
    QListWidget(parent){
}


void ImageListWidget::mousePressEvent(QMouseEvent *event){
        if (event->button() == Qt::LeftButton)
            dragStartPosition = event->pos();
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



    qDebug()<<"ddd";


}

