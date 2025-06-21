//
// Created by patri on 6/8/2025.
//

#include "usuarios.h"

#include <iostream>
usuario::usuario(bool Profe, long Rut, int Contra):profesor(Profe), rut(Rut), contrasena(Contra) {}

void usuario::profecontra() {
    std::string ingresarcontra;
    std::cout << "Ingrese contrasena para acceder como profesor" << std::endl; std::cin>>ingresarcontra;
    if (contrasena == ingresarcontra) {
        profesor = true;
    }
    else {
        profesor = false;
    }
}

//Hola