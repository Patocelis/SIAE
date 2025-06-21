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

/*
struct Asistencia{
    int totalclases;
    int clasesasistidas;
    int justificadas;
    float asist;
};

/*
struct Asignatura {
    std::string nombre;
    unsigned int IDRamo;
    std::deque<Nota> notas;
    Asistencia asistencia;
};
//Estos codigos no parecen ser necesarios ahora mismo, pero no los voy a borrar en caso de ser necesarios

struct InfoAlumno{

    std::string Nombre = "NOMBRE PLACEHOLDER";
    std::deque<Asignatura> asignaturas;
};
*/

struct Curso {
    std::string Nombre = "NombreCurso";
    std::string Sigla = "SiglaPlaceholder";
    int MetodoEvaluacion = 0;
    //Usar strings para calculo de notas segun metodo promedio.
    std::map<std::string, std::deque<Nota>> nota_alumnos;
    //Tiene que haber una forma mejor que esta, solucion temporal
    std::map<std::string, std::deque<std::string>> asist_alumno;
    //Codigo de asistencia conviene mas dentro de curso, para acceder mas facil
};


#endif //ESTADISTICAS_H
