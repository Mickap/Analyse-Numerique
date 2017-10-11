#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QVector>
#include <QtMath>
#include <QDebug>
#include <math.h>
#define NMAX 50

class Traitement
{
public:
    void calculNewton();
    QVector<QVector<double> > DifferencesDivisees();

    QVector<double> X0, Y0, X1, Y1;
    int nb_points;
    double pas;
};

#endif // TRAITEMENT_H
