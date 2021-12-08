#include "connexion.h"
#include <QMessageBox>

connexion::connexion() {}

bool connexion::createconnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("test-bd");
    db.setUserName("jaziri");
    db.setPassword("jaziri");

    if (db.open())
        test=true;

    return test;

}
void connexion ::closeconnexion(){}
