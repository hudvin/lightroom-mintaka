#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QtCore>
#include <QStandardPaths>
#include <QDirIterator>
#include <QFileInfo>
#include <QtDebug>
#include <QStringList>
#include <dbconnector.h>
#include <csvreader.h>

QTextStream cout(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //remove all data from db
    Singleton *dbHolder = Singleton::getInstance();
    dbHolder->getDBWrapper().deleteAllData();
    //load info about files from list.txt
    CSVReader csvReader;
    csvReader.load();
    foreach (PhotoEntry entry, csvReader.getEntries()) {
        dbHolder->getDBWrapper().addPhotoEntry(entry);
        qDebug()<<entry.filename;
    }
    //init main window
    MainWindow w;
    w.setWindowTitle(QString("Lighroom Plugin"));
    w.showMaximized();
    return a.exec();
}
