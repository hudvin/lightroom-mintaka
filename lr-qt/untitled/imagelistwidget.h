#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QAction>
#include <QMenu>
#include <QString>

#include <dbwrapper.h>

class ImageListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ImageListWidget(QWidget *parent = 0);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    void setCurrentKeyword(QString currentKeyword);
    QString getCurrentKeyword();

protected:
   QPoint dragStartPosition;


private:
   QString currentKeyword;
   DBWrapper* dbWrapper = &DBWrapper::GetInstance();

signals:
  void itemWasRemoved();

public slots:
   void showContextMenuForWidget(const QPoint &pos);

};

#endif // IMAGELISTWIDGET_H
