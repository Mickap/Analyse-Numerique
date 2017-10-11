#include "traitement.h"

void Traitement::calculNewton()
{
    QVector<QVector<double> > mat_diff_div; // tableau des différences divisés
    // le pas corresponds à l'intervale entre chaque valeurs de x à interpoler
    double min=1/pas;                       // valeur minimum
    double max=X1.last()*min;               // valeur maximum
    double nb_points_interp=(max-min)+1;    // nombre de points interpolés
    int n=nb_points - 1;                    // indice du dernier élément de X1
    double val_polynome;                    // contiendra chaque point du polynome

    X0.resize(nb_points_interp);
    Y0.resize(nb_points_interp);

    qDebug() << "Calcul des différences divisées :";
    mat_diff_div = DifferencesDivisees();

    qDebug() << "Calcul du polynôme d'interpolation :";
    for (int i = 0; min <= max; min++, i++)
    {
        // Calcul des points X0 d'interpolation
        X0[i] = pas*min;

        // Calcul des points Y0 d'interpolation
        val_polynome = mat_diff_div[0][n];
        for (int j = 1; j <= n; j++)
            val_polynome = val_polynome * (X0[i] - X1[n - j]) + mat_diff_div[0][n - j];
        Y0[i] = val_polynome;

        qDebug().nospace() << "X0=" << X0[i] << "\t Y0=" << Y0[i];
    }
}

QVector<QVector<double> > Traitement::DifferencesDivisees()
{
    int i, j;
    QDebug debug = qDebug();
    QVector<QVector<double>> mat_diff_div(nb_points);
    for (i = 0; i < nb_points; ++i) mat_diff_div[i].resize(nb_points);

    // calcul du premier coefficient
    for (i = 0; i < nb_points; i++)
        mat_diff_div[i][0] = Y1[i];

    // calcul de chaque colonne ligne à ligne
    for (i = 1; i < nb_points; i++)
        for (j = 0; j < nb_points - i; j++)
            mat_diff_div[j][i] = (mat_diff_div[j + 1][i - 1] - mat_diff_div[j][i - 1]) / (X1[j + i] - X1[j]);


    for (i = 0; i <= 4; i++)
    {
        for (j = 0; j <= 4 - i; j++)
            debug << QString::number(mat_diff_div[i][j], 'e', 4);
        debug << endl;
    }

    return mat_diff_div;
}
