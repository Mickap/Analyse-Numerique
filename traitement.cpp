#include "traitement.h"

void Traitement::calcul()
{
    double mat_diff_div[NMAX][NMAX];        // tableau des différences divisés
    // le pas corresponds à l'intervale entre chaque valeurs de x à interpoler
    double min=1/pas;                       // valeur minimum
    double max=X1.last()*min;               // valeur maximum
    double nb_points_interp=(max-min)+1;    // nombre de points interpolés

    X0.resize(nb_points_interp);
    Y0.resize(nb_points_interp);

    DifferencesDivisees(mat_diff_div);

    qDebug() << "Calcul du polynôme d'interpolation :";
    for (int i = 0; min <= max; min++, i++)
    {
        X0[i] = pas*min;
        Y0[i] = Polynome(mat_diff_div, X0[i]);

        qDebug().nospace() << "X0=" << X0[i] << "\t Y0=" << Y0[i];
    }
}

void Traitement::DifferencesDivisees(double mat_diff_div[NMAX][NMAX])
{
    int i, j;

    // Première itération : Xn = Yn
    for (i = 0; i < nb_points; i++)
        mat_diff_div[i][0] = Y1[i];

    for (i = 1; i < nb_points; i++)
        for (j = 0; j < nb_points - i; j++)
            mat_diff_div[j][i] = (mat_diff_div[j + 1][i - 1] - mat_diff_div[j][i - 1]) / (X1[j + i] - X1[j]);


    QDebug debug = qDebug() << "Tableau des différences divisées :" << endl;
    for (i = 0; i <= 4; i++)
    {
        for (j = 0; j <= 4 - i; j++)
            debug << QString::number(mat_diff_div[i][j], 'e', 4);
        debug << endl;
    }
}

double Traitement::Polynome(double mat_diff_div[NMAX][NMAX], double alpha)
{
    double val_polynome;
    int n = nb_points - 1; // nombre de points d'interpolation -1

    val_polynome = mat_diff_div[0][n];
    for (int i = 1; i <= n; i++)
        val_polynome = val_polynome*(alpha - X1[n - i]) + mat_diff_div[0][n - i];

    return val_polynome;
}

