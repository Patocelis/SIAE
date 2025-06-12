
#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H
#include <deque>
#include <iostream>

/*LISTA DE HEADERS QUE NO SE PUEDEN INCLUIR ACA:
 -promedio.h

 */


struct Nota {
    int nota = 0;
    float ponderacion = 100;
    std::string Evaluacion = "Nombre no asignado";
};

struct Asistencia {
    std::string test = "Asistencia PLACEHOLDER";
    //Strings no pueden ser NULL. Se pueden compilar pero fallan al correr
};

struct Asignatura {
    std::string nombre;
    unsigned int IDRamo;
    std::deque<Nota> notas;
    Asistencia asistencia;
};


struct InfoAlumno{

    std::string Nombre = "NOMBRE PLACEHOLDER";
    std::deque<Asignatura> asignaturas;
};



#endif //ESTADISTICAS_H
