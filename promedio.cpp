

#include "promedio.h"
#include <cmath>
#include<deque>
#include<iostream>
#include"toolset.h"
#include "estadisticas.h"

promedio::promedio(int TotalNotas, std::string Operaciones,
    std::deque<Nota> Notas):
    totalnotas(TotalNotas), operaciones(std::move(Operaciones)),
    notas(std::move(Notas)){}
//USAR std::move, los valores de entrada solo seran leidos, asi que no es necesario crear una copia.

void promedio::entradaoperadores() {
    ops.clear();
    for (int i=0; i < operaciones.length(); ++i) {
        operadores O_input;
        O_input.op2 = notas[i].nota * (notas[i].ponderacion / 100);
       // std::cout << notas[i].nota << std::endl;
        //No se por que, pero despues de agregar el print comentado esto funciona
        ops.push_back(O_input);
        std::cout << ops[i].op2 << std::endl;
    }
}

int promedio::notaFinal() {
    entradaoperadores();
    double NotaReturn = -69;
    operaciones += '0';
    std::cout << operaciones << std::endl;
    for (int i=0; i < operaciones.length(); ++i) { // >= y <= No querian funcionar
        if (operaciones[i]=='0') { //RETORNAR VALOR
            NotaReturn = ops[i].op1;
            break;
        }
        if (operaciones[i]=='6') { //PROMEDIAR
            //IMPORTANTE
            //IMPORTANTE
            //PROMEDIAR NO ES NECESARIO CUANDO LOS VALORES
            //SE MULTIPLICAN POR SU PORCENTAJE
            ops[i].op2 = totalnotas;
            ops[i].res = Promediar(ops[i].op1, ops[i].op2);
            ops[i+1].op1 = ops[i].res;
        }
        if (operaciones[i]=='3') { //SUMA
            ops[i].res = Sumar(ops[i].op1, ops[i].op2);
            ops[i+1].op1 = ops[i].res;
            std::cout << "suma " << i+1 << ": " << ops[i].op2 << std::endl;
        }
        if (operaciones[i]=='2') { //MULTIPLICACION
            ops[i].res = Multiplicar(ops[i].op1, ops[i].op2);
            ops[i+1].op1 = ops[i].res;
        }
        if (operaciones[i]=='1') { //POTENCIA
            ops[i].res = Potencia(ops[i].op1, ops[i].op2);
            ops[i+1].op1 = ops[i].res;
        }
        if(operaciones[i]=='4') { //DIVISION
            ops[i].res = Multiplicar(ops[i].op1, Fraccion(ops[i].op2));
            ops[i+1].op1 = ops[i].res;
        }
        if (operaciones[i]=='5') { //RAIZ
            ops[i].res = Potencia(ops[i].op1, Fraccion(ops[i].op2));
            ops[i+1].op1 = ops[i].res;
        }
    }
    if (NotaReturn == -69) {
        std::cout << "ERROR NOTARETURN" << std::endl;
        return -1;
    }
    return std::round(NotaReturn);
}

promedio::~promedio() {
    ops.clear();

}



