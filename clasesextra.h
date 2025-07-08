#ifndef CLASESEXTRA_H
#define CLASESEXTRA_H
#include<string>
using namespace std;

class usuario {
public:
    usuario(string, long, bool);
    string Nombre() const;
    long RUT() const;
    bool Profesor() const;
    bool Contraseña(string intento);

    bool operator<(const usuario& otro) const;
private:
    string nombre;
    long rut;
    string contraseña;
    bool profesor;
};


#endif // CLASESEXTRA_H
