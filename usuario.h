#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <QList>

using namespace std;


class usuario
{
public:
    usuario(string _alias,string _password);
    string get_alias();
    string get_pass();
private:
    string alias;
    string password;


};

#endif // USUARIO_H
