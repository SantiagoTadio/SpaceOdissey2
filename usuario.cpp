#include "usuario.h"

usuario::usuario(string _alias,string _password)
{
    //asignacion del nombre de usuario y contraseña
    alias=_alias;
    password=_password;
}


string usuario::get_alias()
{
    return alias; //retorna el nombre de usuario
}

string usuario::get_pass()
{
    return password; //retorna la contraseña
}
