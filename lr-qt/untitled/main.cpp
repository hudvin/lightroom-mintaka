#include "mainwindow.h"
#include <QLabel>
#include <QtCore>
#include <QStandardPaths>
#include <QDirIterator>
#include <QFileInfo>
#include <QtDebug>
#include <QStringList>
#include <QApplication>
#include <QDir>

#include <csvreader.h>
#include <pathutils.h>

QTextStream cout(stdout, QIODevice::WriteOnly);

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //create app dir
    QDir appDir(PathUtils::getAppTmpDir());
    if(!appDir.exists()){
        appDir.mkpath(PathUtils::getAppTmpDir());
    }
    //remove previous output file
    QFile outputFile(PathUtils::getAppTmpDir() + "/" + Constants::OUTPUT_FILE);
    if(outputFile.exists()){
        outputFile.remove();
    }
    //remove all data from db
    DBWrapper *dbWrapper = &DBWrapper::GetInstance();
    dbWrapper->deleteAllData();
    //load info about files from list.txt
    CSVReader csvReader;
    csvReader.load();
    foreach (PhotoEntry entry, csvReader.getEntries()) {
        dbWrapper->addPhotoEntry(entry);
        qDebug()<<"add to db file: "<<entry.filename;
    }
    //init main window
    MainWindow w;
    w.setWindowTitle(QString("Lighroom Plugin"));
    w.showMaximized();
    return a.exec();
}
