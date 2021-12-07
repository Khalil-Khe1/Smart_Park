#include "jeux.h"
#include <QMessageBox>

JEUX::JEUX()
{

}

JEUX::JEUX(QString id, QString etat, QString type, int ticket, int usage, int totale, int x, int y, QString nom, QString img){
    ID = id;
    Etat = etat;
    Type = type;
    Ticket = ticket;
    Usage_Maintenance = usage;
    Usage_Tot = totale;
    X = x;
    Y = y;
    Nom = nom;
    Image = img;
}

QString JEUX::ConvTracker(){
    QSqlQuery query;
    int row_count = 0;

    query.exec("SELECT COUNT(*) FROM JEUX");
    if(query.first()){
        row_count = query.value(0).toInt();
    }
    QString track = QString::number(row_count);
    int diff = (int) 3 - track.length();
    for(int i = 0; i < diff; i++){
        track = "0" + track;
    }

    return track;
}

bool JEUX::Ajouter(){
    QSqlQuery query;

    QString res2 = QString::number(Ticket);
    QString res3 = QString::number(Usage_Maintenance);
    QString res4 = QString::number(Usage_Tot);
    QString res5 = QString::number(X);
    QString res6 = QString::number(Y);
    query.prepare("INSERT INTO JEUX(ID_JEUX, ETAT, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, NOM, TYPE, IMAGE)""VALUES (:id, :etat, :ticket, :UT, :UM, :x, :y, :nom, :type, :img)");
    query.bindValue(":id", ID);
    query.bindValue(":etat", Etat);
    query.bindValue(":ticket", res2);
    query.bindValue(":UT", res4);
    query.bindValue(":UM", res3);
    query.bindValue(":x", res5);
    query.bindValue(":y", res6);
    query.bindValue(":nom", Nom);
    query.bindValue(":type", Type);
    query.bindValue(":img", Image);
    return query.exec();
}

QSqlQueryModel * JEUX::Afficher(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_JEUX"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TICKET"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("USAGE_TOT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("USAGE_MAINTENANCE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("COORD_X"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("COORD_Y"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("IMAGE"));

    return model;
}

QSqlQueryModel * JEUX::AfficherNom(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT NOM FROM JEUX");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));

    return model;
}

QString JEUX::AfficherImage(QString champ, QString mot){
    QString contenu;
    QSqlQuery query;
    query.prepare("SELECT * FROM JEUX");
    /*QSqlQuery query;
    query.exec("SELECT " + champ + " FROM JEUX WHERE NOM = '" + mot + "'");
    while(query.next()){
        contenu = query.value(0).toString();
    }*/

    return contenu;
}

bool JEUX::Supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM JEUX WHERE ID_JEUX= :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool JEUX::Modifier(QString id){
    QSqlQuery query;
    QString res2 = QString::number(Ticket);
    QString res3 = QString::number(Usage_Maintenance);
    QString res5 = QString::number(X);
    QString res6 = QString::number(Y);
    query.prepare("UPDATE JEUX SET ETAT=:etat, TYPE=:type, TICKET=:ticket, USAGE_MAINTENANCE=:UM, COORD_X=:x, COORD_Y=:y, NOM=:nom, IMAGE=:img WHERE ID_JEUX=:id");
    query.bindValue(":id", id);
    query.bindValue(":etat", Etat);
    query.bindValue(":ticket", res2);
    query.bindValue(":UM", res3);
    query.bindValue(":x", res5);
    query.bindValue(":y", res6);
    query.bindValue(":nom", Nom);
    query.bindValue(":type", Type);
    query.bindValue(":img", Image);
    return query.exec();
}

QSqlQueryModel * JEUX::Tri(int choix, int ordre){
        QSqlQueryModel * model = new QSqlQueryModel();
        QString k;
        if(ordre == 1){
            k = "DESC";
        }
        else {
            k = "ASC";
        }
        switch(choix){
            case 0:
                model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX ORDER BY NOM " + k);
                break;
            case 1:
                model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX ORDER BY TICKET " + k);
                break;
            case 2:
                model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX ORDER BY USAGE_TOT " + k);
                break;
            case 3:
            model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX ORDER BY USAGE_MAINTENANCE " + k);
                break;
            case 4:
                model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX ORDER BY TYPE " + k);
                break;
            case 5:
                model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX ORDER BY ID_JEUX " + k);
                break;
            default:
                break;
        }
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_JEUX"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("TICKET"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("USAGE_TOT"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("USAGE_MAINTENANCE"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("COORD_X"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("COORD_Y"));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("IMAGE"));
        return model;
}

QSqlQueryModel * JEUX::Rechercher(QString mot, int choix)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(choix){
        case 1: //Rechereche nom
            model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX WHERE NOM LIKE '" + mot + "%'");
            break;
        case 2:
            model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX WHERE ID_JEUX LIKE '" + mot + "%'");
            break;
        case 3:
            model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX WHERE ETAT LIKE '" + mot + "%'");
            break;
        case 4:
            model->setQuery("SELECT ID_JEUX, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y, IMAGE FROM JEUX WHERE TYPE LIKE '" + mot + "%'");
            break;
        default:
            break;
    }
    //model->setQuery("SELECT * FROM JEUX WHERE NOM LIKE 'Ar%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_JEUX"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ETAT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("TICKET"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("USAGE_TOT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("USAGE_MAINTENANCE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("COORD_X"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("COORD_Y"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("IMAGE"));

    return model;
}

bool JEUX::Maintenir(QString nom){
    QSqlQuery query;
    QString et = "En Marche";
    QString res = QString::number(300);
    query.prepare("UPDATE JEUX SET ETAT= :etat, USAGE_MAINTENANCE= :UM WHERE NOM = '" + nom + "'");
    query.bindValue(":UM", res);
    query.bindValue(":etat", et);
}

bool JEUX::Jouer(QString mot, int um, int ut, int diff){
    QSqlQuery query;
    QString et = "En Marche";
    if(um <= 0){
        um = 0;
        diff = 0;
        et = "En Panne";
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Attention! Il appéler un technicien pour faire la maintenance.\n"
                                "Click Cancel to exit."), QMessageBox::Ok);
    }
    QString res = QString::number(um - diff);
    QString res2 = QString::number(ut + diff);
    query.prepare("UPDATE JEUX SET ETAT= :etat, USAGE_TOT= :UT, USAGE_MAINTENANCE= :UM WHERE NOM = '" + mot + "'");
    query.bindValue(":UM", res);
    query.bindValue(":UT", res2);
    query.bindValue(":etat", et);

    return query.exec();
}

JEUX::~JEUX(){

}


