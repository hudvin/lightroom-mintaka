#include "pathutils.h"
#include <QStandardPaths>


PathUtils::PathUtils(){


}

QString PathUtils::getAppTmpDir(){
    QString path =
            QStandardPaths::locate(QStandardPaths::TempLocation,
                                   QString(APP_TMP_DIR),
                                   QStandardPaths::LocateDirectory);
   return path;
}
