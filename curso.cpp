#include "curso.h"
#include "clasesextra.h"
#include <string>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "sistema.h"
#include <filesystem>

using namespace std;

curso::curso(string _nombre, string _sigla, long _profe, vector<notas> _plantilla)
    : plantilla(_plantilla), nombre(_nombre), sigla(_sigla), profesor(_profe) {}

string curso::Nombre() const { return nombre; }
string curso::Sigla() const { return sigla; }
long curso::Profesor() const { return profesor; }

map<long, vector<notas>> curso::Nota(long rut) {
    map<long, vector<notas>> salida;
    auto it = alumnos.find(rut);
    if (it != alumnos.end()) {
        salida[rut] = it->second;
    }
    return salida;
}

void curso::genera_plantilla(QWidget* widget) {
    ofstream archivo("plantilla_" + nombre + ".csv");
    string cabeza = "Nombre;RUT;";
    for (size_t i = 0; i < plantilla.size(); ++i) {
        cabeza += plantilla[i].nombre;
        if (i != plantilla.size() - 1) cabeza += ";";
    }
    cabeza += "\n";
    archivo << cabeza;

    for (const auto& par : alumnos) {
        long rut = par.first;
        const vector<notas>& notasAlumno = par.second;
        const usuario* u = sistema->busca_user(rut);
        if (!u) continue;

        string linea = u->Nombre() + ";" + to_string(rut) + ";";
        for (size_t i = 0; i < notasAlumno.size(); ++i) {
            linea += to_string(notasAlumno[i].nota);
            if (i != notasAlumno.size() - 1) linea += ";";
        }
        linea += "\n";
        archivo << linea;
    }

    QMessageBox::information(widget, "Archivo Creado", "El archivo ha sido creado con éxito.");
}

map<string, bool> curso::asis_alumno(long rut, QWidget* ventana) {
    const usuario* u = sistema->busca_user(rut);
    if (!u || u->Profesor()) {
        QMessageBox::critical(ventana, "Error", "Este módulo es solo para alumnos.");
        return {};
    }

    if (alumnos.find(rut) == alumnos.end()) {
        QMessageBox::critical(ventana, "Error", "El alumno no está inscrito en este curso.");
        return {};
    }

    map<string, bool> salida;
    for (const auto& par : asistencia) {
        salida[par.first] = par.second.count(rut) > 0;
    }
    return salida;
}

map<string, set<long>> curso::asis_profe(long rut) {
    const usuario* u = sistema->busca_user(rut);
    if (!u || !u->Profesor()) return {};
    return asistencia;
}

void curso::cargar_plantilla(string ruta) {
    ifstream archivo(ruta);
    string linea;
    plantilla.clear();

    while (getline(archivo, linea)) {
        stringstream lin(linea);
        string campo;
        notas nota;
        int cont = 0;
        while (getline(lin, campo, ';')) {
            if (cont == 0) nota.nombre = campo;
            if (cont == 1) nota.ponderacion = stof(campo);
            cont++;
        }
        nota.nota = 0;
        plantilla.push_back(nota);
    }
}

void curso::carga_masiva(string ruta) {
    ifstream archivo(ruta);
    vector<string> encabezados;
    string linea;

    if (!getline(archivo, linea)) return;
    stringstream linC(linea);
    string campo;
    while (getline(linC, campo, ';')) encabezados.push_back(campo);

    while (getline(archivo, linea)) {
        stringstream lin(linea);
        vector<string> campos;
        while (getline(lin, campo, ';')) campos.push_back(campo);

        if (campos.size() < 2) continue;

        long rut = stol(campos[1]);
        vector<notas> notasAlumno;

        for (size_t i = 2; i < campos.size(); ++i) {
            float valor = stof(campos[i]);
            string nombreNota = encabezados[i];

            auto it = find_if(plantilla.begin(), plantilla.end(),
                              [&nombreNota](const notas& n) { return n.nombre == nombreNota; });

            if (it != plantilla.end()) {
                notas n = *it;
                n.nota = valor;
                notasAlumno.push_back(n);
            }
        }

        alumnos[rut] = notasAlumno;
    }
}

bool curso::tiene_alumno(long rut) const{
    return alumnos.find(rut) != alumnos.end();
}


void curso::set_sistema(Sistema *s){
    sistema = s;
}


void curso::guardar_en_directorio(string ruta) const{
    std::filesystem::create_directories(ruta);  // C++17

    // 1. Guardar plantilla
    std::ofstream plantillaFile(ruta + "/plantilla.csv");
    for (const auto& n : plantilla) {
        plantillaFile << n.nombre << ";" << n.ponderacion << "\n";
    }

    // 2. Guardar alumnos
    std::ofstream alumnosFile(ruta + "/alumnos.csv");
    alumnosFile << "RUT;Nombre";
    for (const auto& n : plantilla) {
        alumnosFile << ";" << n.nombre;
    }
    alumnosFile << "\n";

    for (const auto& [rut, notasAlumno] : alumnos) {
        const usuario* u = sistema->busca_user(rut);
        if (!u) continue;

        alumnosFile << rut << ";" << u->Nombre();
        for (const auto& n : notasAlumno) {
            alumnosFile << ";" << n.nota;
        }
        alumnosFile << "\n";
    }

    // 3. Guardar asistencia (si la manejas)
    std::ofstream asistenciaFile(ruta + "/asistencia.csv");
    asistenciaFile << "Fecha";
    for (const auto& [rut, _] : alumnos) {
        asistenciaFile << ";" << rut;
    }
    asistenciaFile << "\n";

    for (const auto& [fecha, presentes] : asistencia) {
        asistenciaFile << fecha;
        for (const auto& [rut, _] : alumnos) {
            asistenciaFile << ";" << (presentes.count(rut) ? "1" : "0");
        }
        asistenciaFile << "\n";
    }
}

void curso::cargar_asistencia(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) return;

    std::string linea;
    std::vector<long> ruts;

    // Leer encabezado (RUTs)
    if (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string campo;
        std::getline(ss, campo, ';');  // Saltar "Fecha"
        while (std::getline(ss, campo, ';')) {
            try {
                ruts.push_back(std::stol(campo));
            } catch (...) {
                ruts.push_back(0);  // o ignora si prefieres
            }
        }
    }

    // Leer cada fila de asistencia
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string fecha;
        std::getline(ss, fecha, ';');

        std::set<long> presentes;
        std::string valor;
        for (size_t i = 0; i < ruts.size(); ++i) {
            if (!std::getline(ss, valor, ';')) break;
            if (valor == "1") {
                presentes.insert(ruts[i]);
            }
        }

        asistencia[fecha] = presentes;
    }
}
