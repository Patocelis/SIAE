#include "clasesextra.h"

usuario::usuario(string Nombre, long RUT, bool Profe):nombre(Nombre),rut(RUT),profesor(Profe){
    contraseña = nombre;
};

string usuario::Nombre() const{return nombre;}
long usuario::RUT() const{return rut;}
bool usuario::Profesor() const{return profesor;}
bool usuario::Contraseña(string intento){
    if(intento == contraseña){
        return true;
    }else
        return false;
}

void usuario::setContraseña(const std::string& nueva) {
    contraseña = nueva;
}

std::string usuario::getContraseña() const {
    return contraseña;
}

bool usuario::Contraseña(const std::string& intento) const {
    return intento == contraseña;
}
