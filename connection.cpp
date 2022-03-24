#include "connection.h"

Connection::Connection()
{

}



bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("printini");
db.setUserName("asmab");//inserer nom de l'utilisateur
db.setPassword("asma");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
