#include "usuario.h"

usuario::usuario(string _alias,string _password)
{
    alias=_alias;
    password=_password;
}


string usuario::get_alias()
{
    return alias;
}

string usuario::get_pass()
{
    return password;
}
