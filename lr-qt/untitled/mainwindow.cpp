#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QIcon>

#include <QStandardPaths>
#include <QDirIterator>
#include <QFileInfo>
#include <QStringList>
#include <QSize>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString tmpFolderName("mintaka");
    QString ss = QStandardPaths::locate(QStandardPaths::TempLocation, tmpFolderName, QStandardPaths::LocateDirectory);

    QDirIterator dirIt(ss,QDirIterator::Subdirectories);
    ui->lrImages->setIconSize(QSize(250,250));


    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile()){
            if (QFileInfo(dirIt.filePath()).suffix() == "jpg"){
                QListWidgetItem *itm =
                        new QListWidgetItem(QIcon(dirIt.filePath()),"",ui->lrImages);

            }
        }
    }




}

MainWindow::~MainWindow()
{
    delete ui;
}
