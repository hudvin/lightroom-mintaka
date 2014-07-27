#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QPoint>

class ImageListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ImageListWidget(QWidget *parent = 0);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

protected:
   QPoint dragStartPosition;

signals:

public slots:

};

#endif // IMAGELISTWIDGET_H
