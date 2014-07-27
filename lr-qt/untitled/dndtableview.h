#ifndef DNDTABLEVIEW_H
#define DNDTABLEVIEW_H

#include <QTableView>
#include <QDragMoveEvent>

class DndTableView : public QTableView
{
    Q_OBJECT
public:
    explicit DndTableView(QWidget *parent = 0);

protected:

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent * event);


signals:

public slots:

};

#endif // DNDTABLEVIEW_H
