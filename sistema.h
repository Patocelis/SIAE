#ifndef SISTEMA_H
#define SISTEMA_H

#include <map>
#include <vector>
#include <string>
#include "clasesextra.h"

class curso;

class Sistema {
private:
    std::map<long, usuario> usuarios;         // RUT → usuario
    std::vector<curso> cursos;                // Todos los cursos

public:
    // Cargar y guardar usuarios
    void cargar_usuarios(const std::string& ruta);
    void guardar_usuarios(const std::string& ruta);

    // Cargar y guardar cursos
    void cargar_cursos(const std::string& rutaBase);
    void guardar_cursos(const std::string& rutaBase);

    // Autenticación
    bool autenticar(long rut, const std::string& clave, usuario& resultado);

    // Acceso a datos
    std::vector<curso> cursos_del_profesor(long rut) const;
    std::vector<curso> cursos_del_alumno(long rut) const;

    // Registro de usuarios
    void registrar_usuario(const usuario& u);

    // Busca rut, accede al usuario
    const usuario* busca_user(long rut) const;
};

#endif
