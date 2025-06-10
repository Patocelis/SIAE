//
// Created by patri on 6/8/2025.
//

#include "toolset.h"
#include <cmath>
#include <iostream>



double Fraccion(double div) {
    return 1/div;
}

//OPERACIONES:
//POTENCIA: 1
//MULTIPLICACION: 2
//SUMA: 3
//DIVISION: 4
//RAIZ: 5

double Potencia(double op1, double op2) {
    double res = -69;
    res = pow(op1,op2);
    //op1 => Base
    //op2 => Exponente
    if(res == -69) {
        std::cout << "FALLO POTENCIA/RAIZ: " << op1 << " " << op2 << std::endl;
        return -69;
    }
    else return res;
}


double Multiplicar(double op1, double op2) {
    double res = -69;
    res = op1*op2;

    if(res == -69) {
        std::cout << "FALLO MULTIPLICAR: " << op1 << " " << op2 << std::endl;
        return -69;
    }
    else return res;
}


double Sumar(double op1, double op2) {
    double res = -69;
    res = op1 + op2;

    if(res == -69) {
        std::cout << "FALLO SUMAR: " << op1 << " " << op2 << std::endl;
        return -69;
    }
    else return res;
}

double Promediar(double op1, double op2) {
    double res = -69;

    if (op2 == 0){std::cout << "DIVISION ENTRE 0" << std::endl; return 0; }
    res = op1/op2;

    if(res == -69) {
        std::cout << "FALLO PROMEDIAR: " << op1 << " " << op2 << std::endl;
        return -69;
    }
    else return res;
}
