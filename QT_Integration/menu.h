#ifndef MENU_H
#define MENU_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class menu
{
    QString id;
    QString nom;
    float prix;
    QString etat;


public:
    menu();
    menu(QString id,QString nom,float prix,QString etat);
    //getters
    QString getId(){return id;}
    QString getNom(){return nom;}
    float getPrix(){return prix;}
    QString getEtat(){return etat;}
    //setters
    void setId(QString ide){id=ide;}
     void setNom(QString n){nom=n;}
      void setPrix(float p){prix=p;}
       void setEtat(QString e){etat=e;}



     bool ajouter();
     QSqlQueryModel *afficher();
     bool supprimer(QString id);
     void modifier();
     QSqlQueryModel* rechercher(QString id);
     QSqlQueryModel* trie_menuprix();
     void statistique(QVector<double>* ticks,QVector<QString> *labels);



};


#endif // MENU_H
