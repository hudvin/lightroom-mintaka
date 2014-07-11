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

#include <QStandardItem>
#include <QStandardItemModel>

#include <QTableView>
#include <QTableWidgetItem>

QStandardItemModel* createModel(QObject* parent)
{
    const int numRows = 10;
    const int numColumns = 10;

    QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);
    model->setHeaderData(0,Qt::Horizontal, "keyword");
    model->setHeaderData(1,Qt::Horizontal, "number of photos");


    for (int row = 0; row < numRows; ++row)
    {
        for (int column = 0; column < numColumns; ++column)
        {
            QString text = QString('A' + row) + QString::number(column + 1);
            QStandardItem* item = new QStandardItem(text);
            model->setItem(row, column, item);
        }
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

//    QTableWidgetItem *header1 = new QTableWidgetItem();
//    header1->setText("Switch \"ON\" to Load");
//    keywordsTable->setH
//    tableWidget->setHorizontalHeaderItem(0,header1);


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
