#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QVector>
#include <QtMath>
#include <math.h>
#define NMAX 5

class Traitement
{
public:
    Traitement();
    void calcul();
    void DifferencesDivisees(int n, QVector<double> x, QVector<double> f, double d[NMAX][NMAX]);
    double Polynome(int n, double d[NMAX][NMAX], QVector<double> x, double alpha);

    QVector<double> X0, Y0, X1, Y1;
};

#endif // TRAITEMENT_H
