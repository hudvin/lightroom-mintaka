#include "dndtableview.h"
#include <QTableView>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QtGui>


DndTableView::DndTableView(QWidget *parent) : QTableView(parent){
    this->setMouseTracking(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}


void DndTableView::dragEnterEvent(QDragEnterEvent *event){
    event->acceptProposedAction();
}

Keyword DndTableView::getCurrentKeyword(QDropEvent *event){
    QModelIndex modelIndex = this->indexAt(event->pos());
    int row = modelIndex.row();
    QModelIndex firstModelIndex =  this->model()->index(row, 0);
    QString keywordValue = firstModelIndex.data().toString();
    Keyword keyword = dbWrapper.getKeywordByValue(keywordValue);
    return keyword;
}

void DndTableView::dropEvent(QDropEvent *event){
    event->acceptProposedAction();
    QString uuid = event->mimeData()->text();
    PhotoEntry photoEntry = dbWrapper.getPhotoByUUID(uuid);
    Keyword keyword = getCurrentKeyword(event);
    QList<Keyword> keywords =  dbWrapper.getKeywordsForPhoto(dbWrapper.getPhotoByUUID(uuid));
    if(!keywords.contains(keyword)){
        dbWrapper.addKeyword(photoEntry, keyword);
        QSqlQueryModel* model = dynamic_cast <QSqlQueryModel*>
                                               (this->model());
        model->query().exec();
        emit dataChanged(QModelIndex(), QModelIndex());
    }
}

void DndTableView::dragMoveEvent(QDragMoveEvent * event){
    Keyword keyword = getCurrentKeyword(event);
    if(keyword.id!=-1){
        event->acceptProposedAction();
        setCurrentIndex(this->indexAt(event->pos()));
    }
}
