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

#include <QStandardItem>
#include <QStandardItemModel>

#include <QTableView>
#include <QTableWidgetItem>

#include <keywordsloader.h>

#include <QDebug>



void addRowToModel(QStandardItemModel* model,QString firstColumn, QString secondColumn, int rowIdx){

    QStandardItem* keywordItem = new QStandardItem(firstColumn);
    model->setItem(rowIdx, 0, keywordItem);
    //number of photos column
    QStandardItem* counterItem = new QStandardItem(secondColumn);
    model->setItem(rowIdx, 1, counterItem);
}

QStandardItemModel* createModel(QObject* parent){


    KeywordsLoader keywordsLoader;
    QList<QString> keywords = keywordsLoader.load();
    foreach( QString keyword, keywords ){
        qDebug()<<keyword;
    }

    const int numRows = keywords.size();
    const int numColumns = 2;

    QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);
    model->setHeaderData(0,Qt::Horizontal, "keyword");
    model->setHeaderData(1,Qt::Horizontal, "number of \n photos");

    //special row
    addRowToModel(model, "[no keywords]", "0",0);
    for (int row = 1; row < numRows+1; ++row){
        addRowToModel(model, keywords.at(row-1),"0", row);
    }
    return model;
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString tmpFolderName("mintaka");
    QString ss = QStandardPaths::locate(QStandardPaths::TempLocation, tmpFolderName, QStandardPaths::LocateDirectory);

    QDirIterator dirIt(ss,QDirIterator::Subdirectories);
    ui->lrImages->setIconSize(QSize(250,250));

    QTableView* keywordsTable = ui->keywordsTable;
    keywordsTable->setModel(createModel(keywordsTable));


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