#ifndef DNDTABLEVIEW_H
#define DNDTABLEVIEW_H

#include <QTableView>
#include <QDragMoveEvent>
#include <dbconnector.h>


class DndTableView : public QTableView
{
    Q_OBJECT
public:
    explicit DndTableView(QWidget *parent = 0);

protected:

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent * event);

    Keyword getCurrentKeyword(QDropEvent *event);

    Singleton *one = Singleton::getInstance();
    DBWrapper dbWrapper = one->getDBWrapper();

signals:

public slots:

};

#endif // DNDTABLEVIEW_H
