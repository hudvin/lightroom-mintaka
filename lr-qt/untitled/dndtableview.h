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
    void activate();
    QString getCurrentKeyword();

protected:

    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent * event);

    void updateCurrentKeyword(QString keyword);
    Keyword extractCurrentKeyword(QDropEvent *event);

    Singleton *one = Singleton::getInstance();
    DBWrapper dbWrapper = one->getDBWrapper();
    QString currentKeyword;


signals:
    void keywordChanged(const QString &keyword);
    void dataIsDropped();

private slots:
    void clickedSlot(QModelIndex index);




};

#endif // DNDTABLEVIEW_H
