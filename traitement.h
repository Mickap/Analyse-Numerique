#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <QVector>
#include <QtMath>
#include <QDebug>
#define NMAX 50

class Traitement
{
public:
    void calculNewton(double pas);
    void calculerCourbeInitiale(QString nomFonction);
    void calculerPointsInitiaux(int nbPointsInterp, bool randomActive);
    double calculerResidus();
    QVector<double> Xinterp, Yinterp, Xselec, Yselec, Xinit, Yinit;

private:
    QVector<QVector<double> > DifferencesDivisees();
    int nb_points;
};

#endif // TRAITEMENT_H
