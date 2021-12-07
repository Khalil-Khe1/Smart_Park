    #include "menu.h"
#include <iostream>
#include<QDebug>

using namespace std;
menu::menu()
{

}
menu::menu(QString id,QString nom,float pr,QString etat)
{
    this-> id=id;
        this-> nom=nom;
        this-> prix=pr;
        this-> etat=etat;
    }
bool menu::ajouter()
{
    QSqlQuery querry;
    QString prix_s= QString::number(prix);
    querry.prepare("insert into menu (id,nom,prix,etat) values (:id,:nom,:prix,:etat)");
    querry.bindValue(":id",id);
    querry.bindValue(":nom",nom);
    querry.bindValue(":prix",prix_s);
    querry.bindValue(":etat",etat);
    if(querry.exec())
    {qDebug()<<"saved\n";
    return true;
    }

           else{qDebug()<<"not saved!!!\n";
        return false;
    }
}
QSqlQueryModel * menu::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from MENU");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
    return model;
}
void menu::modifier()
{
    QSqlQuery query ;
    QString prix_s= QString::number(prix);
       query.prepare("update  MENU set  id=:id, nom=:nom, prix=:prix,etat=:etat where(id=:id)");
       query.bindValue(":id",id);
       query.bindValue(":nom",nom);
       query.bindValue(":prix",prix_s);
       query.bindValue(":etat",etat);

       if(query.exec())
      {


       qDebug()<<" mis a jour effectuuer!!\n";
   }

    else{ qDebug()<<" echec de la mis a jour!!\n";
}
}
bool menu::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("delete from MENU where (id= :id)");
    query.bindValue(":id", id);
    return query.exec();
}
QSqlQueryModel *menu:: trie_menuprix()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from MENU order by prix,id,nom" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
return model;
}
QSqlQueryModel * menu::rechercher(QString id)

{


    QSqlQueryModel *model=new::QSqlQueryModel;
               model->setQuery("select * from  MENU where ID like '%"+id+"%'or NOM like '%"+id+"%' or PRIX like '%"+id+"%'");
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));
               return model;


}
void menu::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select nom from MENU where prix>10");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
