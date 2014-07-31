#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>

#include <dndtableview.h>
#include <dbwrapper.h>
#include <imagelistwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_generateKeywordsBtn_clicked();
    void on_saveBtn_clicked();

protected slots:
    void reloadAll();


private:
    Ui::MainWindow *ui;
    ImageListWidget* lrImages;
    DndTableView* keywordsTable;
    DBWrapper* dbWrapper = &DBWrapper::GetInstance();
    void MainWindow::showMessageBox(QString text);
};

#endif // MAINWINDOW_H
