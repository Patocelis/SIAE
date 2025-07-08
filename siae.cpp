#include "siae.h"
#include "ui_siae.h"

SIAE::SIAE(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SIAE)
{
    ui->setupUi(this);
    sistema.cargar_usuarios("/bd/usuarios.csv");
    sistema.cargar_cursos("/bd");
}

SIAE::~SIAE()
{
    delete ui;
}
