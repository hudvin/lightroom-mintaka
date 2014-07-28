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


void MainWindow::keywordSelected(const QString &currentKeyword){
    Singleton *one = Singleton::getInstance();
    DBWrapper dbWrapper = one->getDBWrapper();

    ImageListWidget* lrImages = ui->lrImages;
    lrImages->clear();

    QList<PhotoEntry> photos;
    if(currentKeyword=="[without tags]"){
        photos = dbWrapper.getPhotos();
    }else {
        photos = dbWrapper.getPhotosByKeyword(currentKeyword);
    }

    lrImages->setIconSize(QSize(250,250));
    foreach (PhotoEntry phonoEntry, photos) {
        QString fullPath = PathUtils::getAppTmpDir() + "/"+phonoEntry.filename;
        QListWidgetItem *itm = new QListWidgetItem(QIcon(fullPath),"",lrImages);
        itm->setData(5, phonoEntry.uuid);

    }

    lrImages->setAcceptDrops(false);
    lrImages->setDragEnabled(true);

    qDebug()<<currentKeyword;
}

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
    DndTableView* keywordsTable = ui->keywordsTable;

    Singleton *one = Singleton::getInstance();
    DBWrapper dbWrapper = one->getDBWrapper();
    keywordsTable->setModel(dbWrapper.getTagsTableModel());
    keywordsTable->setCurrentIndex( keywordsTable->model()->index(0,0));
    connect(keywordsTable, SIGNAL(keywordChanged(QString)),
                          this, SLOT(keywordSelected(QString)));

    connect(keywordsTable, SIGNAL(dataIsDropped()),
            this, SLOT(dataIsDropped()) );

    keywordsTable->activate();
}

void MainWindow::dataIsDropped(){
    keywordSelected(ui->keywordsTable->getCurrentKeyword());
    qDebug()<<"changed";
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
          //  showMessageBox(value.toString());
        }
     }
}


void MainWindow::showMessageBox(QString text){
    QMessageBox m;
    m.setText(text);
    m.exec();
}

