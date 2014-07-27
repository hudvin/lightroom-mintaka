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
    model->setQuery("SELECT tag, (SELECT COUNT(*) FROM photos_tags "\
                    "WHERE photos_tags.tag_id=tags.id ) as num " \
                    "FROM tags WHERE is_hidden=0 " \
                    "UNION " \
                    " SELECT '[without tags]', " \
                    "(SELECT COUNT(*) FROM photos " \
                    "WHERE photos.id NOT IN(SELECT photos_tags.photo_id FROM photos_tags)) as num "
                    );

   // model->removeColumn(0);
    model->setHeaderData(1, Qt::Horizontal, "Tag");
    return model;
}

