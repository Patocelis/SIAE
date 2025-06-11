#include <iostream>
#include <cmath>
#include<deque>
#include"toolset.h"
#include"promedio.h"
#include"Estadisticas.h"

int main() {

    InfoAlumno TEST;
    TEST.asignaturas.push_back(Asignatura()); //Inicializar Structs para evitar crasheos


    TEST.asignaturas[0].nombre = "MAT060";
    TEST.asignaturas[0].IDRamo = 060;

    for (int i=0; i < 6; ++i) {
        Nota NotaTemp;
        NotaTemp.Evaluacion = "NOMBRE NO ASIGNADO";
        NotaTemp.nota = 0;
        NotaTemp.ponderacion = 100;

        std::cout << "INGRESAR NOTA " << i+1 << ": " << std::endl;
        std::cin >> NotaTemp.nota;

       // std::cout << "INGRESAR PONDERACION " << i+1 << ": " << std::endl;
       // std::cin >> NotaTemp.ponderacion;


        std::cout << "INGRESAR NOMBRE DE EVALUACION" << i+1 << " : " << std::endl;
        std::cin >> NotaTemp.Evaluacion;

        TEST.asignaturas[0].notas.push_back(NotaTemp);
    }
    //Mientras estoy haciendo este codigo y trato de que quede ordenado y corto
    //Veo los 20000 ifs que usa undertale y solo quiero llorar



    /*std::deque<int> Notas{60, 3, 70, 3, 45, 3};*/
    std::deque<float> Porcentajes{16.67,16.67,16.67,16.67,16.67,16.67};
    std::string Operaciones;

    std::cout << "ORDEN OPERACIONES: " <<
                 "\nPOTENCIA: 1\nMULTIPLICACION: 2" <<
                "\nSUMA: 3\nDIVISION: 4\nRAIZ: 5 " <<
                    std::endl;

    std::cin >> Operaciones;

    promedio PromTest(6, Operaciones,
        TEST.asignaturas[0].notas,
        //TEST.asignaturas[0].notas[0]); //TODO: AGREGAR METODO PARA MOVER PONDERACION DESDE STRUCT A PROMEDIO
        Porcentajes);
    int PromFinal = PromTest.notaFinal();
    std::cout << "PROMEDIO FINAL: " << PromFinal << std::endl;

    //Probando que es commit
    //Probando subida manual

}
