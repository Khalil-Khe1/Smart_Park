
#include "staff.h"

staff::staff(int id ,QString nom ,QString prenom ,QString fonction,QDate date)
{
    this->ID=id ;
    this->nom=nom ;
    this->prenom=prenom;
    this->fonction=fonction ;
    this->date_de_naissance=date ;
}
bool staff::ajouter()
{
    QSqlQuery query;
    QString res =QString::number(ID);
    query.prepare("insert into STAFF(ID_STAFF , NOM , PRENOM , FONCTION , DATE_NAISSANCE) values(:id , :nom , :prenom ,:fonction ,:date_naissance)");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":fonction",fonction);
    query.bindValue(":date_naissance",date_de_naissance);
    return query.exec();//exec() envoie la requete pour l'executer


}
QSqlQueryModel * staff::afficher ()
{
   QSqlQueryModel * model =new QSqlQueryModel();

    //model->setQuery("select * form staff");
   model->setQuery("SELECT nom, prenom , id_staff , fonction , date_naissance FROM staff");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("fonction"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("date de naissance"));
    return model ;

}


bool staff::supprimer(int id)
{
QSqlQuery query ;
QString res=QString::number(id);
query.prepare("Delete from staff where ID_STAFF= :id");
query.bindValue(":id",res);
return query.exec();
}
//test ajout fichier tutorial git

 bool staff:: modifier(int id ,QString nom,QString prenom,QString fonction,QDate date_naissance)
 {
     QSqlQuery query ;
     QString id_string = QString::number(id);
     query.prepare("update STAFF set nom=:nom,prenom=:prenom,fonction=:fonction,date_naissance=:date_naissance where id_staff=:id_staff");
     query.bindValue(":id_staff",id_string);
     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":fonction",fonction);
     query.bindValue(":date_naissance",date_naissance);
     return query.exec();
}

 QSqlQueryModel* staff::triparAge()
 {
 QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM staff order by date_naissance ASC");
                  q->exec();
                  model->setQuery(*q);
                  model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
                  model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
                  model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
                  model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
                  model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
                  return model;


 }
 QSqlQueryModel* staff::rechercher_nom(QString nom)
 {
     QSqlQuery * q = new  QSqlQuery ();

                      QSqlQueryModel * model = new  QSqlQueryModel ();
                      q->prepare("select * from staff where nom=:nom");
                      q->bindValue(":nom",nom );
                      q->exec();

          model->setQuery(*q);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));


         return model;

 }
 QSqlQueryModel* staff::rechercher_prenom(QString prenom)
 {

     QSqlQuery * q = new  QSqlQuery ();

                      QSqlQueryModel * model = new  QSqlQueryModel ();
                      q->prepare("select * from Gestion_client where prenom=:prenom");
                      q->bindValue(":prenom",prenom );
                      q->exec();

          model->setQuery(*q);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));


         return model;

 }
 QSqlQueryModel* staff::rechercher_id(int id)
 {

     QSqlQuery * q = new  QSqlQuery ();

                      QSqlQueryModel * model = new  QSqlQueryModel ();
                      q->prepare("select * from staff where id_staff=:id");
                      q->bindValue(":id",id );
                      q->exec();

          model->setQuery(*q);
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));


         return model;

 }
 QSqlQueryModel * staff::rechercher_nomprenom(QString nom, QString prenom)
 {
     QSqlQuery *qry= new QSqlQuery();
     QSqlQueryModel *model = new QSqlQueryModel();
     qry->prepare("select * from staff where prenom=:prenom and nom=:nom");
     qry->bindValue(":prenom",prenom);
     qry->bindValue(":nom",nom);
     qry->exec();

        model->setQuery(*qry);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));

         return model;


 }
 QSqlQueryModel * staff::rechercher_nomid(QString nom, int idC)
 {
     QSqlQuery *qry= new QSqlQuery();
     QString id_string=QString::number(idC);
     QSqlQueryModel *model = new QSqlQueryModel();
     qry->prepare("select * from staff where idC=:idC and nom=:nom");
     qry->bindValue(":id_staff",id_string );
     qry->bindValue(":nom",nom);
     qry->exec();

        model->setQuery(*qry);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));

         return model;


 }
 QSqlQueryModel * staff::rechercher_prenomid(QString prenom, int idC)
 {
     QSqlQuery *qry= new QSqlQuery();
     QString id_string=QString::number(idC);
     QSqlQueryModel *model = new QSqlQueryModel();
     qry->prepare("select * from staff where id_staff=:id and prenom=:prenom");
     qry->bindValue(":id_staff",id_string );
     qry->bindValue(":prenom",prenom);
     qry->exec();

        model->setQuery(*qry);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("fonction"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));

         return model;


 }
 QSqlQueryModel * staff::rechercher_prenom_id_nom(QString prenom, int idC,QString nom)
 {
     QSqlQuery *qry= new QSqlQuery();
     QString id_string=QString::number(idC);
     QSqlQueryModel *model = new QSqlQueryModel();
     qry->prepare("select * from staff where id_staff=:id and prenom=:prenom and nom=:nom");
     qry->bindValue(":id_staff",id_string );
     qry->bindValue(":prenom",prenom);
     qry->bindValue(":nom",nom);
     qry->exec();

        model->setQuery(*qry);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_staff"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse_mail"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));

         return model;


 }

 void staff::calendrier(QTextCharFormat f,QCalendarWidget * w)
 {
     QDate date;
     QSqlQuery query("SELECT date_naissance FROM staff");
     while (query.next())
     {
         date=query.value(0).toDate();
         w->setDateTextFormat(date,f);
     }
     w->setDateTextFormat(date,f);
 }

 void staff::statistiques(QWidget * w)
 {
         int nb1 = 0,nb2=0,nb3=0,nb4=0;
             QSqlQuery query("SELECT COUNT(*) FROM staff WHERE fonction='Technicien'");
             while(query.next())
             {
                 nb1 = query.value(0).toInt();
             }
             QSqlQuery query2("SELECT COUNT(*) FROM staff WHERE fonction='Ingenieur'");
             while(query2.next())
             {
                nb2= query2.value(0).toInt();
             }
             QSqlQuery query3("SELECT COUNT(*) FROM staff WHERE fonction='PDG'");
             while(query3.next())
             {
                nb3= query3.value(0).toInt();
             }
             QSqlQuery query4("SELECT COUNT(*) FROM staff WHERE fonction='Staff'");
             while(query4.next())
             {
                nb4= query4.value(0).toInt();
             }

         QPieSeries *series = new QPieSeries();

         series->append("Technicien",nb1);
         series->append("Ingenieur",nb2);
         series->append("PDG",nb3);
         series->append("Staff",nb4);

         series->setHoleSize(0.0);
         series->setPieSize(1.0);
         QPieSlice * T = series->slices().at(0);
         QPieSlice * I = series->slices().at(1);
         QPieSlice * P = series->slices().at(2);
         QPieSlice * S = series->slices().at(3);

         T->setLabelVisible(true);
         I->setLabelVisible(true);
         P->setLabelVisible(true);
         S->setLabelVisible(true);

         T->setBrush(QColor::fromRgb(255, 0, 0));
         I->setBrush(QColor::fromRgb(0, 255, 0));
         P->setBrush(QColor::fromRgb(0, 0, 255));
         S->setBrush(QColor::fromRgb(255, 255, 0));

         QChart *chart = new QChart();
         chart->addSeries(series);
         chart->setTitle("Fonctions");
         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignBottom);
         chart->setAnimationOptions(QChart::AllAnimations);

         QChartView * chartview = new QChartView(chart);
         chartview->resize(w->width(),w->height());
         chartview->setParent(w);
 }
