#ifndef SIAE_H
#define SIAE_H
#include "sistema.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SIAE;
}
QT_END_NAMESPACE

class SIAE : public QMainWindow
{
    Q_OBJECT

public:
    SIAE(QWidget *parent = nullptr);
    Sistema sistema;
    ~SIAE();

private:
    Ui::SIAE *ui;
};
#endif // SIAE_H
