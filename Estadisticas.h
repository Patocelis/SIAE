//
// Created by patri on 6/8/2025.
//
#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H
#include <deque>
#include <iostream>
#include "toolset.h"
#include "Promedio.h"

struct Nota {
    float ponderacion = 100;
    std::string Evaluacion = "Nombre no asignado";
};

struct Asistencia {
    std::string test = "PLACEHOLDER ASISTENCIA";
};

struct Asignatura {
    std::string nombre;
    std::deque<Nota> notas;
};


struct InfoAlumno{

    std::string Nombre = "NOMBRE PLACEHOLDER";
    Asignatura Ramo;
    Asistencia AsistenciaAlumno;
};



#endif //ESTADISTICAS_H
