#include "dndtableview.h"
#include <QTableView>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QtGui>
#include <QStyledItemDelegate>

class StyledItemDelegate : public QStyledItemDelegate
{
public:
        StyledItemDelegate(QObject *parent = NULL) :
          QStyledItemDelegate(parent) {}
          void paint(QPainter *painter, const QStyleOptionViewItem &option,
                  const QModelIndex &index) const{
              QStyleOptionViewItemV4 opt = option;
                  initStyleOption(&opt, index);
              initStyleOption(&opt, index);
              qDebug()<<"drop action "<< (option.state==QStyle::State_MouseOver);
//              qDebug()<<"focus";
//                  QStyleOptionViewItem opt = option;
//                //  if(opt.state!=QStyle::State_Selected){
//                 //     opt.state = QStyle::State_Selected;

//               //   }
              //    QStyledItemDelegate::paint(painter, option, index);


              if((option.state & QStyle::State_MouseOver)){

//                  QColor color(255,255,130,100);
//                      QColor colorEnd(255,255,50,150);
//                      QLinearGradient gradient(option.rect.topLeft(),option.rect.bottomRight());
//                      gradient.setColorAt(0,color);
//                      gradient.setColorAt(1,colorEnd);
//                      QBrush brush(gradient);
//                      painter->fillRect(option.rect,brush);

          } else {
                  QStyledItemDelegate::paint(painter, option, index);

              }

          }
};

DndTableView::DndTableView(QWidget *parent) : QTableView(parent){
  this->setMouseTracking(true);
//    setAcceptDrops(true);
//    setDragEnabled(true);
//    setDragDropMode(QAbstractItemView::DragDrop);
//    viewport()->setAcceptDrops(true);
//    setDropIndicatorShown(true);

  //  setItemDelegate(new StyledItemDelegate(this));
       setSelectionMode(QAbstractItemView::SingleSelection);
       setSelectionBehavior(QAbstractItemView::SelectRows);


//    setDropIndicatorShown(true);
//    setDragDropOverwriteMode(true);
//    viewport()->setAcceptDrops(true);

//    setDragDropMode(QAbstractItemView::DragDrop);
//    setDefaultDropAction(Qt::CopyAction);


}


void DndTableView::dragEnterEvent(QDragEnterEvent *event){
    event->acceptProposedAction();
}

void DndTableView::dropEvent(QDropEvent *event){
    event->acceptProposedAction();
    QModelIndex modelIndex = this->indexAt(event->pos());
    int row = modelIndex.row();
    QModelIndex firstModelIndex =  this->model()->index(row, 0);
    QString keyword = firstModelIndex.data().toString();
    qDebug()<<"position"<<keyword<<" : "<<event->mimeData()->text();
}

void DndTableView::dragMoveEvent(QDragMoveEvent * event){
    event->acceptProposedAction();
    QModelIndex modelIndex = this->indexAt(event->pos());
    setCurrentIndex(modelIndex);
}
