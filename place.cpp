#include "place.h"
#include <QMessageBox>
#include <QUrl>
#include <QSqlRecord>
#include <QTableView>
#include <QSqlQueryModel>
#include "qcustomplot.h"
place::place(int num,QString type ,QString etat,QString bloc,int places)
{
    this->num=num;
    this->type=type;
    this->etat=etat;
    this->bloc=bloc;
    this->places=places;

}
bool place ::ajouter()
{
    QSqlQuery query;
    QString res = QString :: number(num);
    query.prepare("insert into GESTION_PLACE_PARKING(num,type,etat,bloc,places)""values(:num,:type,:etat,:bloc,:places)");
    query.bindValue(":num",res);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":bloc",bloc);
    query.bindValue(":places",places);


    return query.exec();
}
QSqlQueryModel * place :: afficher()
{

QSqlQueryModel * model=new QSqlQueryModel ();

model->setQuery("select * from GESTION_PLACE_PARKING");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUM"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("BLOC"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("PLACES"));

return model;
}
bool place ::supprimer(int num)
{
QSqlQuery query;
QString res=QString ::number(num);
query.prepare("delete from GESTION_PLACE_PARKING where num= :num");
query.bindValue(":num",res);
return query.exec();
}
bool place:: modifier(int num)
{
    QSqlQuery query;
    QString res=QString ::number(num);

    query.prepare("UPDATE GESTION_PLACE_PARKING SET num=:num,type=:type,etat=:etat where num=:num");
    query.bindValue(":num",res);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":bloc",bloc);


    return query.exec();
}
QSqlQueryModel * place::recherche_place(int num)
{
QSqlQuery q;
q.prepare("select * from GESTION_PLACE_PARKING where num=:num");
q.bindValue(":num", num);
q.exec();
QSqlQueryModel * model = new QSqlQueryModel;
model->setQuery(q);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("bloc"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("places"));

QSqlRecord rec = model->record(0);
int nou = rec.value("num").toInt();
if( nou ==num ){
    return model;
  }
return nullptr;
}
QSqlQueryModel * place::recherche_bloc(QString bloc)
{
QSqlQuery q;
q.prepare("select * from GESTION_PLACE_PARKING where bloc=:bloc");
q.bindValue(":bloc", bloc);
q.exec();
QSqlQueryModel * model = new QSqlQueryModel;
model->setQuery(q);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("bloc"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("places"));

QSqlRecord rec = model->record(0);
QString nou = rec.value("bloc").toString();
if( nou ==bloc ){
    return model;
  }
return nullptr;
}
QSqlQueryModel * place::recherche_places(int places)
{
QSqlQuery q;
q.prepare("select * from GESTION_PLACE_PARKING where places=:places");
q.bindValue(":places", places);
q.exec();
QSqlQueryModel * model = new QSqlQueryModel;
model->setQuery(q);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("etat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("bloc"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("places"));

QSqlRecord rec = model->record(0);
int nou = rec.value("places").toInt();
if( nou ==places ){
    return model;
  }
return nullptr;
}


QSqlQueryModel* place::tri()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from GESTION_PLACE_PARKING order by num");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("etat"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("bloc"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("places"));


   return model;

}
void place::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select bloc from GESTION_PLACE_PARKING");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
QSqlQueryModel* place::tri_bloc()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from GESTION_PLACE_PARKING order by bloc");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("etat"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("bloc"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("places"));


   return model;

}
QSqlQueryModel* place::tri_places()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from GESTION_PLACE_PARKING order by places");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("etat"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("bloc"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("places"));


   return model;

}
int place::numbre(QString block)
{
    QSqlQuery q;
    int i=0;
    q.exec("select bloc from GESTION_PLACE_PARKING where block=:bloc");
    while (q.next())
    {

        i++;

    }
    return i;
}
