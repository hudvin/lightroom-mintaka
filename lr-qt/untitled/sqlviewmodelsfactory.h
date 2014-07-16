#ifndef SQLVIEWMODELSFACTORY_H
#define SQLVIEWMODELSFACTORY_H

#include <QSqlDatabase>
#include <QSqlRelationalTableModel>


class SQLViewModelsFactory{
public:
    SQLViewModelsFactory();
    QSqlRelationalTableModel* getKeywordsTableModel(QSqlDatabase* db);
    QSqlQueryModel* getTagsTableModel(QSqlDatabase* db);


};

#endif // SQLVIEWMODELSFACTORY_H
