#include "dndtableview.h"
#include <QTableView>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QtGui>
#include <QStyledItemDelegate>
#include <dbconnector.h>


DndTableView::DndTableView(QWidget *parent) : QTableView(parent){
    this->setMouseTracking(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}


void DndTableView::dragEnterEvent(QDragEnterEvent *event){
    event->acceptProposedAction();
}

void DndTableView::dropEvent(QDropEvent *event){
    event->acceptProposedAction();
    QModelIndex modelIndex = this->indexAt(event->pos());
    int row = modelIndex.row();
    QModelIndex firstModelIndex =  this->model()->index(row, 0);
    QString keywordValue = firstModelIndex.data().toString();
    QString uuid = event->mimeData()->text();
    qDebug()<<"position"<<keywordValue<<" : "<<event->mimeData()->text();

    Singleton *one = Singleton::getInstance();
    DBWrapper dbWrapper = one->getDBWrapper();
    PhotoEntry photoEntry = dbWrapper.getPhotoByUUID(uuid);
    Keyword keyword = dbWrapper.getKeywordByValue(keywordValue);
    qDebug()<<keyword.id;
    qDebug()<<photoEntry.id;
    dbWrapper.addKeyword(photoEntry, keyword);

    QSqlQueryModel* model = dynamic_cast <QSqlQueryModel*>
                                       (this->model());
    model->query().exec();
    emit dataChanged(QModelIndex(), QModelIndex());
}

void DndTableView::dragMoveEvent(QDragMoveEvent * event){
    event->acceptProposedAction();
    QModelIndex modelIndex = this->indexAt(event->pos());
    setCurrentIndex(modelIndex);
}
