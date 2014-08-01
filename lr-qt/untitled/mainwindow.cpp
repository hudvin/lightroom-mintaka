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
#include <QSharedPointer>
#include <QThread>
#include <QTimer>

#include <csvreader.h>
#include <keywordsloader.h>
#include <dbwrapper.h>
#include <pathutils.h>
#include <constants.h>
#include <keywordsextractor.h>
#include <keywordsextractorstrategy.h>

void MainWindow::reloadAll(){
    QString currentKeyword = keywordsTable->getCurrentKeyword();
    lrImages->clear();
    lrImages->setCurrentKeyword(currentKeyword);

    QList<PhotoEntry> photos;
    if(currentKeyword == Constants::Keywords::WITHOUT_KEYWORDS){
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
        itm->setData(Constants::MagicNumbers::DATA_KEY, phonoEntry.uuid);
    }

    lrImages->setAcceptDrops(false);
    lrImages->setDragEnabled(true);
    keywordsTable->reloadData();
}


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);

    lrImages = ui->lrImages;
    keywordsTable = ui->keywordsTable;

    keywordsTable->setModel(dbWrapper->getTagsTableModel());

    keywordsTable->setCurrentIndex(keywordsTable->model()->index(1,0));

    connect(keywordsTable, SIGNAL(pleaseReload()),this, SLOT(reloadAll()));
    connect(keywordsTable, SIGNAL(pleaseReload()), this, SLOT(reloadAll()) );
    connect(lrImages, SIGNAL(pleaseReload()),this, SLOT(reloadAll()) );

    keywordsTable->activate();
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_generateKeywordsBtn_clicked(){
    QList<PhotoEntry> photos = dbWrapper->getAllPhotos();

    KeywordsExtractor* ke =
            new KeywordsExtractor(QSharedPointer<RandomKeywordsExtractorStrategy>(new RandomKeywordsExtractorStrategy),this);
    ke->addPhotoEntries(photos);

    int numTasks = photos.size();
    QProgressDialog* dialog = new QProgressDialog("Generating keywords", "Cancel", 0, numTasks, this);
    dialog->setWindowModality(Qt::WindowModal);
    disconnect(dialog, SIGNAL(canceled()), dialog, SLOT(cancel()));
    dialog->setValue(ke->getProcessedCount());
    connect(dialog, &QProgressDialog::canceled, [=]() {
        ke->stop();
     });
    connect(ke, SIGNAL(valueChanged(int)), dialog, SLOT(setValue(int)));
    connect(ke, &KeywordsExtractor::finished, [=](){
        dialog->cancel();
        qDebug() <<"close dialog";
        showMessageBox("finished");
    });
    ke->startExtraction();
    dialog->show();
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


void MainWindow::showMessageBox(QString text){
    QMessageBox m;
    m.setText(text);
    m.exec();
}

