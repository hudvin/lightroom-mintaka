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

void DndTableView::reloadData(){
    QSqlQueryModel* model = dynamic_cast <QSqlQueryModel*>
                                           (this->model());
    model->query().exec();
    emit dataChanged(QModelIndex(), QModelIndex());
}

void DndTableView::activate(){
    selectRow(0);
    setFocus();
    updateCurrentKeyword(model()->index(0, 0).data().toString());
    connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(clickedSlot(QModelIndex)));
}

void DndTableView::clickedSlot(const QModelIndex index){
    if (index.isValid()) {
        QModelIndexList list  = selectionModel()->selectedRows();
        QVariant value =  list.at(0).data(0);
        if(value.isValid()){
            updateCurrentKeyword(value.toString());
        }
    }
}


void DndTableView::updateCurrentKeyword(QString keyword){
    if (currentKeyword!=keyword){
        currentKeyword = keyword;
        //emit signal
        emit keywordChanged(currentKeyword);
    }
}

QString DndTableView::getCurrentKeyword(){
    return currentKeyword;
}

void DndTableView::dragEnterEvent(QDragEnterEvent *event){
    event->acceptProposedAction();
}

Keyword DndTableView::extractCurrentKeyword(QDropEvent *event){
    QModelIndex modelIndex = this->indexAt(event->pos());
    int row = modelIndex.row();
    QModelIndex firstModelIndex =  this->model()->index(row, 0);
    QString keywordValue = firstModelIndex.data().toString();
    Keyword keyword = dbWrapper->getKeywordByValue(keywordValue);
    return keyword;
}

void DndTableView::dropEvent(QDropEvent *event){
    event->acceptProposedAction();
    QString uuid = event->mimeData()->text();
    PhotoEntry photoEntry = dbWrapper->getPhotoByUUID(uuid);
    Keyword keyword = extractCurrentKeyword(event);
    QList<Keyword> keywords =  dbWrapper->getKeywordsForPhoto(dbWrapper->getPhotoByUUID(uuid));
    if(!keywords.contains(keyword)){
        dbWrapper->addKeyword(photoEntry, keyword);
        reloadData();
        emit dataIsDropped();
    }
}

void DndTableView::dragMoveEvent(QDragMoveEvent * event){
    Keyword keyword = extractCurrentKeyword(event);
    if(keyword.id!=-1){
        event->acceptProposedAction();
        setCurrentIndex(this->indexAt(event->pos()));
    }
}
