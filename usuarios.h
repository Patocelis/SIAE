//
// Created by patri on 6/8/2025.
//

#ifndef USUARIOS_H
#define USUARIOS_H
#include<string>

class usuario{
    std::string rol;
    bool profesor;
    std::string Nombre;
    long rut;
    std::string contrasena;
public:
    usuario(bool, long, std::string);
    void profecontra();
    std::string getNombre();
};



#endif //USUARIOS_H
