#ifndef JEUX_H
#define JEUX_H

#include <QApplication>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class JEUX
{
    private:
        QString ID;
        QString Etat;
        QString Type;
        int Ticket;
        int Usage_Maintenance;
        int Usage_Tot;
        int X;
        int Y;
        QString Nom;
        QString Image;

    public:
        JEUX();
        JEUX(QString, QString, QString, int, int, int, int, int, QString, QString);
        QString ConvTracker();
        bool Ajouter();
        QSqlQueryModel * Afficher();
        QSqlQueryModel * AfficherNom();
        QString AfficherImage(QString, QString);
        bool Modifier(QString);
        bool Supprimer(QString);
        QSqlQueryModel * Rechercher(QString, int);
        QSqlQueryModel * Tri(int, int);
        bool Jouer(QString, int, int, int);
        bool Maintenir(QString);
        ~JEUX();
};

#endif // JEUX_H
