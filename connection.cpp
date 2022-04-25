#include "connection.h"

Connection::Connection()
{

}


bool Connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("lunatics");
    db.setUserName("joseph");//inserer nom de l'utilisateur
    db.setPassword("guetat");//inserer mot de passe de cet utilisateur

    if (db.open()){
     test=true;
    }

    return  test;
}
