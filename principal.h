#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include "ui_principal.h"
#include "qcustomplot.h"
#include "traitement.h"
#include <math.h>

class Principal : public QMainWindow, private Ui::Principal
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = 0);

private slots:
    void makePlot();
    void afficherPoint(QCPAbstractPlottable *courbe, int, QMouseEvent*);
    void calculerPoints(bool);
    void ajoutPoint(bool);
    void supprPoint(bool);
private:
    QCPItemLine *fleche;
    QCPItemText *etiquette;
    Traitement traitement;
};

#endif // PRINCIPAL_H
