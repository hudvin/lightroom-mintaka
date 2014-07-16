#include <QString>
#include <QList>

#include <structures.h>

#ifndef CSVREADER_H
#define CSVREADER_H

#define ENTRIES_FILE_NAME "list.txt"


class CSVReader
{
public:
    CSVReader();
    void load();
    bool isUUIDInList(QString uuid);
    QList<PhotoEntry> getEntries();

private:
    QList<PhotoEntry> entries;

};

#endif // CSVREADER_H
