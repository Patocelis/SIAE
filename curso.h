#ifndef CURSO_H
#define CURSO_H
#include<string>
#include<map>
#include<vector>
#include"clasesextra.h"
#include<set>
#include<QWidget>

using namespace std;

struct notas
{
    string nombre;
    float nota = 0;
    float ponderacion;
};


class curso{
public:
    curso(string _nombre, string _sigla, usuario _profe,vector<notas>);
    string Nombre(); //
    string Sigla(); //
    string Profesor(); //
    map<usuario, vector<notas> > Nota(usuario); //
    vector<float> est_asist(usuario);
    void mod_nota(usuario);
    void carga_masiva(string, QWidget *ventana);//Puta mierda
    void genera_plantilla(QWidget* widget); //
    map<string,set<usuario> > asis_profe(usuario); //
    map<string, bool> asis_alumno(usuario en_linea,QWidget *ventana);//
    void agregarAlumno(usuario u, const vector<notas>& n);
    string get_nombre() const { return nombre; }
    string get_sigla() const { return sigla; }
private:
    vector<notas> plantilla;
    string nombre;
    string sigla;
    string profesor;
    map<usuario,vector<notas> > alumnos;
    map<string,set<usuario> > asistencia;
    int total_seciones;
};

#endif // CURSO_H
