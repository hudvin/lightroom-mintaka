#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_keywordsTable_clicked(const QModelIndex &index);


private:
    Ui::MainWindow *ui;
    void MainWindow::showMessageBox(QString text);
};

#endif // MAINWINDOW_H
