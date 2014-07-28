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
#include <QList>
#include <QString>
#include <QMessageBox>
#include <QProgressDialog>

#include <QStandardItem>
#include <QStandardItemModel>

#include <QTableView>
#include <QTableWidgetItem>


#include <csvreader.h>

#include <keywordsloader.h>
#include <dbwrapper.h>

#include <QDebug>
#include <dbconnector.cpp>
#include <QSqlRelationalTableModel>

#include <pathutils.h>

#include <QDragEnterEvent>
#include <QDropEvent>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->lrImages->setIconSize(QSize(250,250));
    QTableView* keywordsTable = ui->keywordsTable;

    Singleton *one = Singleton::getInstance();
    DBWrapper dbWrapper = one->getDBWrapper();
    keywordsTable->setModel(dbWrapper.getTagsTableModel());
    foreach (PhotoEntry phonoEntry, dbWrapper.getPhotos()) {
        QString fullPath = PathUtils::getAppTmpDir() + "/"+phonoEntry.filename;
        QListWidgetItem *itm = new QListWidgetItem(QIcon(fullPath),"",ui->lrImages);
        itm->setData(5, phonoEntry.uuid);

    }
    ui->lrImages->setAcceptDrops(false);
    ui->lrImages->setDragEnabled(true);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_generateKeywordsBtn_clicked(){
    showMessageBox("Generate keywords");
    int numTasks = 100000;
    QProgressDialog progress("Task in progress...", "Cancel", 0, numTasks, this);
    progress.setWindowModality(Qt::WindowModal);

    for (int i = 0; i < numTasks; i++) {
        progress.setValue(i);
        if (progress.wasCanceled()){
          break;
        }
    }
    progress.setValue(numTasks);
}

void MainWindow::on_saveBtn_clicked(){
    showMessageBox("Save keywords");
}

void MainWindow::on_keywordsTable_clicked(const QModelIndex &index){
    if (index.isValid()) {
        QTableView* keywordsTable = ui->keywordsTable;
        QModelIndexList list  = keywordsTable->selectionModel()->selectedRows();
        QVariant value =  list.at(0).data(0);
        if(value.isValid()){
            showMessageBox(value.toString());
        }
     }
}


void MainWindow::showMessageBox(QString text){
    QMessageBox m;
    m.setText(text);
    m.exec();
}

