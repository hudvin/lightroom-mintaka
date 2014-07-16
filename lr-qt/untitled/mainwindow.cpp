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


#include <sqlviewmodelsfactory.h>


#include <keywordsloader.h>
#include <dbwrapper.h>

#include <QDebug>
#include <dbconnector.cpp>
#include <QSqlRelationalTableModel>



void addRowToModel(QStandardItemModel* model,QString firstColumn, QString secondColumn, int rowIdx){

    QStandardItem* keywordItem = new QStandardItem(firstColumn);
    model->setItem(rowIdx, 0, keywordItem);
    //number of photos column
    QStandardItem* counterItem = new QStandardItem(secondColumn);
    model->setItem(rowIdx, 1, counterItem);
}

QStandardItemModel* createModel(QObject* parent){
    DBWrapper dbWrapper;

    Singleton *one = Singleton::getInstance();
    QList<Tag> tags =  one->getDBWrapper().getVisibleTags();



    //QList<Tag> tags = dbWrapper.getVisibleTags();

    const int numRows =  tags.size(); //keywords.size();
    const int numColumns = 2;

    QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);
    model->setHeaderData(0,Qt::Horizontal, "keyword");
    model->setHeaderData(1,Qt::Horizontal, "number of \n photos");

    //special row
    addRowToModel(model, "[no keywords]", "0",0);

    for (int row = 1; row < numRows+1; ++row){
        addRowToModel(model, tags.at(row-1).tag,"0", row);
    }
    return model;
}


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){


    ui->setupUi(this);
    ui->lrImages->setIconSize(QSize(250,250));

    QTableView* keywordsTable = ui->keywordsTable;

    Singleton *one = Singleton::getInstance();
    SQLViewModelsFactory* f = new SQLViewModelsFactory();
    QSqlQueryModel* tm = f->getTagsTableModel(&one->getDBWrapper().getDatabase());

    //tm->removeColumn(0);
    //tm->removeColumn(3);
   // tm->setFilter("is_hidden==0");
   // tm->setHeaderData(1, Qt::Horizontal,QObject::tr("keyword"));
   // tm->setHeaderData(2, Qt::Horizontal,QObject::tr("number\n of photos"));



    keywordsTable->setModel(tm);






    //    keywordsTable->setModel(createModel(keywordsTable));


    QString tmpFolderName("mintaka");
    QString ss = QStandardPaths::locate(QStandardPaths::TempLocation, tmpFolderName, QStandardPaths::LocateDirectory);
    QDirIterator dirIt(ss,QDirIterator::Subdirectories);

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
        if (progress.wasCanceled())
          break;
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
