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
    void calcul();
    void DifferencesDivisees(double mat_diff_div[NMAX][NMAX]);
    double Polynome(double mat_diff_div[NMAX][NMAX], double alpha);

    QVector<double> X0, Y0, X1, Y1;
    int nb_points;
    double pas;
};

#endif // TRAITEMENT_H
