#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QList>
#include <QStringList>
namespace Constants{

   const QString OUTPUT_FILE = "output.csv";

   namespace Database {

       const QString FILE_NAME = "database.db";

   }

   namespace Keywords {

       const QString WITHOUT_KEYWORDS = "[without keywords]";
       const QString ALL_PHOTOS = "[all]";
       const QList<QString> DEFAULT_KEYWORDS = QList<QString>()<< "people"<<"mountain"<<"valley"<<"landscape"<<"building" ;

   }

   namespace MagicNumbers{

       const int DATA_KEY = 5;

   }


}


#endif // CONSTANTS_H
