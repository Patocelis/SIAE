#include "asistenciadialog.h"
#include <QVBoxLayout>
#include <QLabel>

AsistenciaDialog::AsistenciaDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Asistencia");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("Aquí puedes mostrar la asistencia del alumno.", this);
    layout->addWidget(label);
    setLayout(layout);
}
