//
// Created by patri on 6/8/2025.
//

#ifndef TOOLSET_H
#define TOOLSET_H

double Fraccion(double div);
double Potencia(double op1, double op2);
double Multiplicar(double op1, double op2);
double Sumar(double op1, double op2);
double Promediar(double op1, double op2);

struct operadores {
    double op1 = 0;
    double op2 = 0;
    double res;
};



//int Porcentaje(double inputfloat);
//PENDIENTE PORCENTAJE



#endif //TOOLSET_H
