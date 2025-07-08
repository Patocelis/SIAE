#include "curso.h"
#include "clasesextra.h"
#include <string>
#include <QMessageBox>
#include<fstream>
#include<QWidget>
#include"clasesextra.h"
#include <vector>



using namespace std;
curso::curso(string _nombre, string _sigla, usuario _profe, vector<notas> _plantilla):
    plantilla(_plantilla),
    nombre(_nombre),
    sigla(_sigla),
    profesor(_profe.Nombre()){}

string curso::Nombre(){return nombre;}
string curso::Sigla(){return sigla;}
string curso::Profesor(){return profesor;}

map<usuario, vector<notas> > curso::Nota(usuario en_linea){
    if(en_linea.Profesor()){
        return alumnos;
    }else{
        map<usuario, vector<notas> > salida;
        try{
            alumnos.at(en_linea);
            salida.insert(*alumnos.find(en_linea));
            return salida;
        }catch(const exception e){
            return salida;
        }
    }
}
void curso::agregarAlumno(usuario u, const vector<notas>& n) {
    alumnos[u] = n;
}
void curso::genera_plantilla(QWidget* widget){
    ofstream archivo("plantilla_"+nombre);
    string cabeza = "Nombre;RUT;";
    for(vector<notas>::iterator it = plantilla.begin(); it != plantilla.end(); it++){
        cabeza += it->nota;
        if(it != plantilla.end()){
            cabeza += ";";
        }else{
            cabeza += "\n";
        }
    }
    archivo << cabeza;

    for(map<usuario,vector<notas> >::iterator it = alumnos.begin(); it != alumnos.end(); it++){
        string linea = it->first.Nombre() + ";" + to_string(it->first.RUT());
        for(vector<notas>::iterator _it = it->second.begin(); _it != it->second.end(); _it++){
            linea += to_string(_it->nota);
            if(_it != it->second.end()-1) linea += ";";
        }
        linea += "\n";
    }

    QMessageBox::information(widget,"Archivo Creado", "El archivo a sido creado con exito.");
}

map<string, bool> curso::asis_alumno(usuario en_linea, QWidget *ventana) {
    // Esto es solo un ejemplo simulado. Puedes reemplazarlo con tu lógica real.
    map<string, bool> asistencia;

    asistencia["Semana 1"] = true;
    asistencia["Semana 2"] = false;
    asistencia["Semana 3"] = true;
    asistencia["Semana 4"] = true;

    return asistencia;
}



map<string,set<usuario> > curso::asis_profe(usuario en_linea){
    if(! en_linea.Profesor()) return {};
    else return asistencia;
}

/*void curso::carga_masiva(string _archivo, QWidget *ventana){
    vector<string> cabeza;
    ifstream archivo(_archivo);
    if(! archivo.is_open()){
        QMessageBox::critical(ventana,"Error!!","El archivo no se pudo leer");
        return;
    }

    string linea; // lee la primera linea
    getline(archivo,linea);
    stringstream teno(linea);
    string campo;
    while(getline(teno,campo,';'))cabeza.push_back(campo);

    while(getline(archivo,linea)){
        stringstream lineaS(linea);
        string campo;
        int contador = 0;
        vector<notas> notas;

        while(getline(lineaS,campo,';')){
            if(contador == 2){

            }
        }
    }
}*/

/*void curso::carga_masiva(std::string _archivo, QWidget *ventana) {
    std::vector<std::string> encabezados;
    std::ifstream archivo(_archivo);

    if (!archivo.is_open()) {
        QMessageBox::critical(ventana, "Error", "El archivo no se pudo leer.");
        return;
    }

    std::string linea;

    // Leer encabezados
    if (!std::getline(archivo, linea)) {
        QMessageBox::warning(ventana, "Archivo vacío", "El archivo no contiene datos.");
        return;
    }

    std::stringstream encabezadoStream(linea);
    std::string campo;
    while (std::getline(encabezadoStream, campo, ';')) {
        encabezados.push_back(campo);
    }

    int total = 0;
    while (std::getline(archivo, linea)) {
        std::stringstream lineaStream(linea);
        std::vector<std::string> campos;
        std::string campo;

        while (std::getline(lineaStream, campo, ';')) {
            campos.push_back(campo);
        }

        if (campos.size() < 2) continue;  // Se espera al menos RUT y nombre

        try {
            long rut = std::stol(campos[0]);
            std::string nombre = campos[1];
            usuario nuevoAlumno(nombre, rut, false);  // false porque no es profesor

            std::vector<notas> notasAlumno;

            for (size_t i = 2; i < campos.size(); ++i) {
                try {
                    float valor = std::stof(campos[i]);
                    std::string nombreNota = encabezados[i];

                    // Buscar en la plantilla
                    auto it = std::find_if(plantilla.begin(), plantilla.end(),
                                           [&nombreNota](const notas& n) {
                                               return n.nombre == nombreNota;
                                           });

                    if (it != plantilla.end()) {
                        notas notaCopia = *it;
                        notaCopia.nota = valor;
                        notasAlumno.push_back(notaCopia);
                    }
                } catch (...) {
                    // Ignorar errores de conversión de nota
                }
            }

            alumnos[nuevoAlumno] = notasAlumno;
            ++total;

        } catch (...) {
            // Ignorar errores de conversión de RUT
        }
    }

    archivo.close();
    QMessageBox::information(ventana, "Carga exitosa",
                             QString("Se cargaron %1 alumnos correctamente.").arg(total));
}
*/
