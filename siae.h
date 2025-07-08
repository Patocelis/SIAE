#ifndef SIAE_H
#define SIAE_H

#include <QMainWindow>
#include <QPushButton>
#include <QMap>
#include <QVBoxLayout>

#include "clasesextra.h"
#include "curso.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SIAE;
}
QT_END_NAMESPACE

class SIAE : public QMainWindow
{
    Q_OBJECT

public:
    explicit SIAE(QWidget *parent = nullptr);
    ~SIAE();
private slots:
    void mostrarVentanaAsistencia();
private:
    Ui::SIAE *ui;

    // Datos del sistema
    usuario usuario_conectado;
    curso* curso_activo = nullptr;

    // Widgets dinámicos
    QMap<QString, QPushButton*> botonesNotas;

    // Funciones internas
    vector<curso*> cursos_disponibles;
    void mostrarVistaCursos();
    void seleccionarCurso(curso* seleccionado);
    void crearBotonesNotas();
    void mostrarVistaNotas();
    void mostrarVistaAsistencia();
};

#endif // SIAE_H
