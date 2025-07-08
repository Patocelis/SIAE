#ifndef CLASESEXTRA_H
#define CLASESEXTRA_H
#include<string>
using namespace std;

class usuario{
public:
    usuario(string, long, bool);
    string Nombre() const;
    long RUT() const;
    bool Profesor()const;
    bool Contraseña(string intento);
    void setContraseña(const std::string& nueva);
    std::string getContraseña() const;
    bool Contraseña(const std::string& intento) const;

private:
    string nombre;
    long rut;
    string contraseña;
    bool profesor;
};


#endif // CLASESEXTRA_H
