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
#include <QDebug>
#include <QSqlRelationalTableModel>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFile>
#include <QTextStream>

#include <csvreader.h>
#include <keywordsloader.h>
#include <dbwrapper.h>
#include <pathutils.h>
#include <constants.h>
#include <constants.h>


void MainWindow::keywordSelected(const QString &currentKeyword){
    lrImages->clear();
    lrImages->setCurrentKeyword(currentKeyword);

    QList<PhotoEntry> photos;
    if(currentKeyword== Constants::Keywords::WITHOUT_KEYWORDS){
        photos = dbWrapper->getPhotosWithoutTags();
    } else if(currentKeyword == Constants::Keywords::ALL_PHOTOS){
        photos = dbWrapper->getAllPhotos();
    }else {
        photos = dbWrapper->getPhotosByKeyword(currentKeyword);
    }

    lrImages->setIconSize(QSize(200,400));
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
    lrImages = ui->lrImages;
    keywordsTable = ui->keywordsTable;

    keywordsTable->setModel(dbWrapper->getTagsTableModel());
    keywordsTable->setCurrentIndex(keywordsTable->model()->index(0,0));
    connect(keywordsTable, SIGNAL(keywordChanged(QString)),
                          this, SLOT(keywordSelected(QString)));

    connect(keywordsTable, SIGNAL(dataIsDropped()),
            this, SLOT(dataIsDropped()) );


    connect(lrImages, SIGNAL(itemWasRemoved()),
            this, SLOT(dataIsDropped()) );


    keywordsTable->activate();
}


void MainWindow::dataIsDropped(){
    keywordSelected(ui->keywordsTable->getCurrentKeyword());
    keywordsTable->reloadData();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_generateKeywordsBtn_clicked(){
    int numTasks = 100000;
    QProgressDialog progress("Generating keywords", "Cancel", 0, numTasks, this);
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
    // format:   filename, uuid, tags
    //save to AppData output.txt
    QStringList csvData;
    foreach (PhotoEntry photo, dbWrapper->getAllPhotos()) {
        QStringList lineData;
        QList<Keyword> keywords = dbWrapper->getKeywordsForPhoto(photo);
        lineData+=photo.filename;
        lineData+=photo.uuid;
        foreach (Keyword keyword, keywords) {
           lineData+=keyword.keyword;
        }
        csvData+=lineData.join(",");
    }
    QString appTmpDir = PathUtils::getAppTmpDir();
    QString filePath =appTmpDir + "/" + Constants::OUTPUT_FILE;

    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        foreach (const QString &str, csvData){
            stream << str << endl;
        }
    }
    showMessageBox("Saved");
}

//void MainWindow::on_keywordsTable_clicked(const QModelIndex &index){
//    if (index.isValid()) {
//        QTableView* keywordsTable = ui->keywordsTable;
//        QModelIndexList list  = keywordsTable->selectionModel()->selectedRows();
//        QVariant value =  list.at(0).data(0);
//        if(value.isValid()){
//          //  showMessageBox(value.toString());
//        }
//     }
//}


void MainWindow::showMessageBox(QString text){
    QMessageBox m;
    m.setText(text);
    m.exec();
}

