#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <QList>

using namespace std;


class usuario
// objeto con informacion de usuario
{
public:
    usuario(string _alias,string _password); // construye el usuario con su alias y contraseña
    string get_alias(); //retorna el alias
    string get_pass(); //retorna la contraseña
private:
    string alias;
    string password;


};

#endif // USUARIO_H
