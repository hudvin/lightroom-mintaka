#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include <dbwrapper.h>

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
    void keywordSelected(const QString &currentKeyword);
    void dataIsDropped();


private:
    Ui::MainWindow *ui;
    DBWrapper* dbWrapper = &DBWrapper::GetInstance();
    void MainWindow::showMessageBox(QString text);
};

#endif // MAINWINDOW_H
