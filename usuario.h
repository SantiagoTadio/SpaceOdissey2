#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <QList>

using namespace std;

class usuario
{
public:
    usuario();
    QList<string*> partidas;
    string Alias(){return  alias;}
    string Clave(){return  clave;}
    void setAlias(string nom){alias = nom;}
    void setClave(string con){clave= con;}
private:
    string alias, clave;

};

#endif // USUARIO_H
