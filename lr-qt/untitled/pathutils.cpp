#include "pathutils.h"
#include <QStandardPaths>
#include <QDebug>

PathUtils::PathUtils(){

    qDebug()<<getAppTmpDir();

}

QString PathUtils::getAppTmpDir(){
    QString path =  QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    return path;
}
