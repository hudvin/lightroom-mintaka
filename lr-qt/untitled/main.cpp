#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QtCore>
#include <QStandardPaths>
#include <QDirIterator>
#include <QFileInfo>
#include <QtDebug>
#include <QStringList>

QTextStream cout(stdout, QIODevice::WriteOnly);


int main(int argc, char *argv[])
{
    QString tmpFolderName("mintaka");
    QString ss = QStandardPaths::locate(QStandardPaths::TempLocation, tmpFolderName, QStandardPaths::LocateDirectory);

    cout<<ss<<endl;

    QDirIterator dirIt(ss,QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile()){
            if (QFileInfo(dirIt.filePath()).suffix() == "jpg"){
                qDebug()<<dirIt.filePath();
            }
        }
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString("Lighroom Plugin"));
    w.showMaximized();
    return a.exec();
}
