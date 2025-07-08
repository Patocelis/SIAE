// siae.cpp
#include "siae.h"
#include "ui_siae.h"
#include "asistenciadialog.h"

#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

SIAE::SIAE(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SIAE)
    , usuario_conectado("Alumno Test", 12345678, false)
{
    ui->setupUi(this);
    connect(ui->botonCursosFijo, &QPushButton::clicked, this, &SIAE::mostrarVistaCursos);
    connect(ui->botonNotasFijo, &QPushButton::clicked, this, &SIAE::mostrarVistaNotas);
    connect(ui->botonAsistenciaFijo, &QPushButton::clicked, this, &SIAE::mostrarVistaAsistencia);
    // Simular plantilla de notas
    vector<notas> plantilla = {
        {"C.1", 72, 20},
        {"C.2", 62, 35},
        {"C.3", 81, 20},
        {"Controles", 50, 25},
    };

    // Crear curso y asignar plantilla
    vector<notas> plantilla1 = {
        {"C.1", 75, 30}, {"C.2", 68, 30}, {"Proyecto", 85, 40}
    };

    vector<notas> plantilla2 = {
        {"Control 1", 60, 50}, {"Control 2", 80, 50}
    };

    curso* curso1 = new curso("Matemática 1", "MAT101", usuario_conectado, plantilla1);
    curso* curso2 = new curso("Programación", "INF120", usuario_conectado, plantilla2);

    // Asignar notas
    curso1->agregarAlumno(usuario_conectado, plantilla1);
    curso2->agregarAlumno(usuario_conectado, plantilla2);

    // Agregar a la lista de cursos
    cursos_disponibles.push_back(curso1);
    cursos_disponibles.push_back(curso2);

    // Mostrar la vista inicial de cursos
    mostrarVistaCursos();

    // Mostrar visualmente
    crearBotonesNotas();
}
void SIAE::seleccionarCurso(curso* seleccionado)
{
    curso_activo = seleccionado;
    mostrarVistaNotas();
}
void SIAE::mostrarVistaCursos()
{
    QVBoxLayout* layout = ui->Visualizadornotas;

    // Limpiar layout
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    QLabel* titulo = new QLabel("<b>Seleccione un curso:</b>", this);
    layout->addWidget(titulo);

    for (curso* c : cursos_disponibles) {
        QString nombreCurso = QString::fromStdString(c->get_nombre()) + " (" + QString::fromStdString(c->get_sigla()) + ")";
        QPushButton* boton = new QPushButton(nombreCurso, this);

        layout->addWidget(boton);

        connect(boton, &QPushButton::clicked, this, [=]() {
            seleccionarCurso(c);
        });
    }

    ui->label->clear();  // Limpiar label derecho
}
void SIAE::mostrarVistaNotas()
{
    if (!curso_activo) return;

    QVBoxLayout* layout = ui->Visualizadornotas;

    // Limpiar vista anterior
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) delete item->widget();
        delete item;
    }

    auto notas_map = curso_activo->Nota(usuario_conectado);
    if (notas_map.empty()) return;

    auto notas_vector = notas_map.begin()->second;
    float ponderado = 0;

    for (const notas& n : notas_vector) {
        QPushButton* boton = new QPushButton(QString::fromStdString(n.nombre), this);
        layout->addWidget(boton);

        connect(boton, &QPushButton::clicked, this, [=]() {
            QString info;
            info += "<b>Nombre:</b> " + QString::fromStdString(n.nombre) + "<br>";
            info += "<b>Nota:</b> " + QString::number(n.nota) + "<br>";
            info += "<b>Ponderación:</b> " + QString::number(n.ponderacion) + "%";
            ui->label->setText(info);
        });

        ponderado += n.nota * n.ponderacion / 100.0f;
    }

    // Mostrar fórmula del promedio
    QString formula = "NF = ";
    for (size_t i = 0; i < notas_vector.size(); ++i) {
        formula += QString::fromStdString(notas_vector[i].nombre) + "*" +
                   QString::number(notas_vector[i].ponderacion) + "%";
        if (i < notas_vector.size() - 1) formula += " + ";
    }

    QLabel* etiquetaFormula = new QLabel(this);
    etiquetaFormula->setText("<b>Fórmula Promedio:</b><br>" + formula);
    layout->addWidget(etiquetaFormula);

    QLabel* etiquetaFinal = new QLabel(this);
    etiquetaFinal->setText("<b>Ponderacion Final:</b> " + QString::number(ponderado));
    layout->addWidget(etiquetaFinal);
    float nota_final = 0;
    for (const notas& n : notas_vector) {
        nota_final += n.nota * n.ponderacion / 100.0f;
    }

    // Mostrar en label derecho (QLabel de arriba a la derecha)
}

void SIAE::crearBotonesNotas()
{
    mostrarVistaNotas();
}
void SIAE::mostrarVistaAsistencia()
{
    if (!curso_activo) return;

    QVBoxLayout* layout = ui->Visualizadornotas;
    if (!layout) return;

    // Limpiar widgets anteriores
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Obtener la asistencia del usuario
    auto asistencia_map = curso_activo->asis_alumno(usuario_conectado, this);

    QString texto;
    if (!asistencia_map.empty()) {
        texto += "<b>Asistencia por sección:</b><br><ul>";
        for (const auto& par : asistencia_map) {
            texto += "<li>" + QString::fromStdString(par.first) + ": " + (par.second ? "Presente" : "Ausente") + "</li>";
        }
        texto += "</ul>";

        // Calcular porcentaje
        int total = asistencia_map.size();
        int presentes = std::count_if(asistencia_map.begin(), asistencia_map.end(),
                                      [](const auto& p) { return p.second; });

        float porcentaje = total > 0 ? 100.0f * presentes / total : 0.0f;
        texto += "<br><b>Asistencia Total:</b> " + QString::number(porcentaje, 'f', 2) + "%";
    } else {
        texto = "No hay datos de asistencia.";
    }

    QLabel* asistenciaLabel = new QLabel(texto, this);
    asistenciaLabel->setTextFormat(Qt::RichText);
    layout->addWidget(asistenciaLabel);
}
void SIAE::mostrarVentanaAsistencia()
{
    AsistenciaDialog* ventana = new AsistenciaDialog(this);
    ventana->exec();  // Ventana modal
}
SIAE::~SIAE()
{
    delete ui;
}

