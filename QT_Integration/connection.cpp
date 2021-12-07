#include "connection.h"
//Test tutoriel git
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("khalil1");//inserer nom de l'utilisateur
db.setPassword("esprit21");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
