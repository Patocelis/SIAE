//
// Created by patri on 6/8/2025.
//

#ifndef USUARIOS_H
#define USUARIOS_H
#include<string>

class usuario{
    bool profesor;
    std::string Nombre;
    long rut;
    int contraseña;
public:
    usuario(bool, long, int);
    bool profe();
    std::string getNombre();
};



#endif //USUARIOS_H
