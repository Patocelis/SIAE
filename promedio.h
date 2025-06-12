//
// Created by patri on 6/7/2025.
//

#ifndef PROMEDIO_H
#define PROMEDIO_H
#include <cmath>
#include<deque>
#include<iostream>
#include "toolset.h"
#include "Estadisticas.h"




class promedio {
public:
    promedio(int TotalNotas, std::string Operaciones,
    std::deque<Nota> Notas);
    ~promedio();
    std::deque<operadores> ops;
    void entradaoperadores();
    std::deque<Nota> notas;
    std::string operaciones;
    int totalnotas;
    int notaFinal();

};



#endif //PROMEDIO_H
