#ifndef CURSO_H
#define CURSO_H
#include<string>
#include<map>
#include<vector>
#include<set>
#include<QWidget>

using namespace std;

struct notas
{
    string nombre;
    float nota = 0;
    float ponderacion;
};

class Sistema;

class curso{
public:
    curso(string _nombre, string _sigla, long _profe,vector<notas> _plantilla);
    string Nombre() const; //
    string Sigla() const; //
    long Profesor() const; //
    map<long, vector<notas> > Nota(long); //
    vector<float> est_asist(long);
    void mod_nota(long,notas);
    void cargar_plantilla(string ruta);//
    void genera_plantilla(QWidget* widget); //
    void carga_masiva(string ruta); //
    map<string,set<long> > asis_profe(long); //
    map<string, bool> asis_alumno(long en_linea,QWidget *ventana);//
    void guardar_en_directorio(string) const;//
    bool tiene_alumno(long) const;//
    void set_sistema(Sistema* s);//
    void cargar_asistencia(const std::string& ruta);
private:
    vector<notas> plantilla;
    string nombre;
    string sigla;
    long profesor;
    map<long,vector<notas> > alumnos;
    map<string,set<long> > asistencia;
    int total_seciones;
    Sistema* sistema = nullptr;
};

#endif // CURSO_H
