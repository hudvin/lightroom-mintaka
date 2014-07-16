#include "sqlviewmodelsfactory.h"
#include <QSqlRelationalTableModel>


SQLViewModelsFactory::SQLViewModelsFactory(){
}

QSqlRelationalTableModel* SQLViewModelsFactory::getKeywordsTableModel(QSqlDatabase *db){
    // QSqlQuery query("SELECT id, tag FROM tags WHERE is_hidden=0", db);
    QSqlRelationalTableModel* model=new QSqlRelationalTableModel();
    model->setTable("tags");
    model->select();
    return model;
}

QSqlQueryModel* SQLViewModelsFactory::getTagsTableModel(QSqlDatabase* db){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id, tag FROM tags WHERE is_hidden=0");
    model->removeColumn(0);
    model->setHeaderData(1, Qt::Horizontal, "Tag");
    //model->setHeaderData(1, Qt::Horizontal, tr("Salary"));
    return model;
}

