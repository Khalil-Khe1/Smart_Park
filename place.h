#ifndef PLACE_H
#define PLACE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QSqlTableModel>
#include <QUrl>
#include <QSqlRecord>
class place
{
    int num,places;

    QString type,etat,bloc;

public:
    place (){}
    place(int,QString,QString,QString,int);
    //
    int  getnum(){return num;}
    QString getetat(){return etat;}
    QString gettype (){return type;}
    QString getbloc (){return bloc;}
    int  getplaces(){return places;}


    //

    void setetat(QString e){etat=e;}
    void settype(QString t){type=t;}
    void setnum(int n){num=n;}
    void setbloc(QString b){bloc=b;}
    void setplaces(int pla){places=pla;}


    //
    QSqlQueryModel * afficher();
    bool ajouter();
    bool modifier (int num);
    bool supprimer (int num);
    QSqlQueryModel * recherche_place(int num);
    QSqlQueryModel * recherche_bloc(QString bloc);
    QSqlQueryModel * recherche_places(int places);
    QSqlQueryModel *tri();
    void statistique(QVector<double>* ticks,QVector<QString> *labels);
   QSqlQueryModel* tri_bloc();
   QSqlQueryModel* tri_places();
   int numbre(QString q);
};

#endif // PLACE_H
