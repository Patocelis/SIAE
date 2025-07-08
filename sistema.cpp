#include"sistema.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "clasesextra.h"
#include "curso.h"
#include <map>

bool Sistema::autenticar(long rut, const std::string& clave, usuario& resultado) {
    auto it = usuarios.find(rut);
    if (it != usuarios.end() && it->second.Contraseña(clave)) {
        resultado = it->second;
        return true;
    }
    return false;
}

void Sistema::cargar_usuarios(const std::string& ruta) {
    std::ifstream archivo(ruta);
    std::string linea;
    std::getline(archivo, linea); // Saltar encabezado

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string rutStr, nombre, clave, esProfeStr;
        std::getline(ss, rutStr, ';');
        std::getline(ss, nombre, ';');
        std::getline(ss, clave, ';');
        std::getline(ss, esProfeStr, ';');

        long rut = std::stol(rutStr);
        bool esProfe = (esProfeStr == "1");

        usuario u(nombre, rut, esProfe);
        usuarios[rut] = u;
    }
}

void Sistema::guardar_usuarios(const std::string& ruta) {
    std::ofstream archivo(ruta);
    archivo << "RUT;Nombre;Contraseña;EsProfesor\n";
    for (const auto& [rut, u] : usuarios) {
        archivo << rut << ";" << u.Nombre() << ";" << u.getContraseña() << ";" << u.Profesor() << "\n";
    }
}

void Sistema::cargar_cursos(const std::string& rutaBase) {
    std::ifstream archivo(rutaBase + "/cursos.csv");
    std::string linea;
    std::getline(archivo, linea); // Saltar encabezado

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string sigla, nombre, rutProfeStr;
        std::getline(ss, sigla, ';');
        std::getline(ss, nombre, ';');
        std::getline(ss, rutProfeStr, ';');

        long rutProfe = std::stol(rutProfeStr);

        curso c(nombre, sigla, rutProfe, {});
        c.cargar_plantilla(rutaBase + "/cursos/" + sigla + "/plantilla.csv");
        c.carga_masiva(rutaBase + "/cursos/" + sigla + "/alumnos.csv");
        c.cargar_asistencia(rutaBase + "/cursos/" + sigla + "/asistencia.csv");

        cursos.push_back(c);
    }
}

void Sistema::guardar_cursos(const std::string& rutaBase) {
    std::ofstream archivo(rutaBase + "/cursos.csv");
    archivo << "Sigla;Nombre;RUT_Profesor\n";
    for (const auto& c : cursos) {
        archivo << c.Sigla() << ";" << c.Nombre() << ";" << c.Profesor() << "\n";
        c.guardar_en_directorio(rutaBase + "/cursos/" + c.Sigla());
    }
}

std::vector<curso> Sistema::cursos_del_profesor(long rut) const {
    std::vector<curso> resultado;
    for (const auto& c : cursos) {
        if (c.Profesor() == rut) resultado.push_back(c);
    }
    return resultado;
}

std::vector<curso> Sistema::cursos_del_alumno(long rut) const {
    std::vector<curso> resultado;
    for (const auto& c : cursos) {
        if (c.tiene_alumno(rut)) resultado.push_back(c);
    }
    return resultado;
}

const usuario* Sistema::busca_user(long rut) const {
    auto it = usuarios.find(rut);
    if (it != usuarios.end()) {
        return &(it->second);
    } else {
        return nullptr;
    }
}
