#include "clasesextra.h"

#include "clasesextra.h"

usuario::usuario(string Nombre, long RUT, bool Profe)
    : nombre(Nombre), rut(RUT), profesor(Profe) {
    contraseña = nombre;
}


string usuario::Nombre() const { return nombre; }
long usuario::RUT() const { return rut; }
bool usuario::Profesor() const { return profesor; }

bool usuario::Contraseña(string intento) {
    return intento == contraseña;
}


bool usuario::operator<(const usuario& otro) const {
    return rut < otro.rut;
}
