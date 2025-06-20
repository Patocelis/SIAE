#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H
#include <deque>
#include <iostream>
#include <map>
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
    std::string rol;
    int totalclases;
    int clasesasistidas;
    int justificadas;
    float asist;
    std::map<std::string, std::deque<std::string>> asist_alumno;
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
