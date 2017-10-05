#include "traitement.h"

Traitement::Traitement()
{
    // 5 points donnés à l'algorithme par défaut
    // f(1)=4, f(4)=2, f(5)=1, f(6)=3, f(9)=3

    X1.resize(NMAX);
    Y1.resize(NMAX);
    X1[0] = 1; X1[1] = 4; X1[2] = 5; X1[3] = 6; X1[4] = 9;
    Y1[0] = 4; Y1[1] = 2; Y1[2] = 1; Y1[3] = 3; Y1[4] = 3;
}

void Traitement::calcul()
{
    X0.resize(33);
    Y0.resize(33);

    double alpha, ord;
    int i, j;
    double d[NMAX][NMAX];

    DifferencesDivisees(4, X1, Y1, d);
    /*printf("Tableau des différences divisées\n");
    for (i = 0; i <= 4; i++)
    {
        for (j = 0; j <= 4 - i; j++)
            printf("%14.4e", d[i][j]);
        printf("\n");
    }*/

    // printf("Calcul du polynôme d'interpolation\n");
    for (j = 4, i = 0; j <= 36; j++, i++)
    {
        alpha = 0.25*j;
        ord = Polynome(4, d, X1, alpha);
        // printf("x =%6.2f     y =%24.16e\n", alpha, ord);

        // envoie les 33 valeurs interpolés à la 1er courbe
        X0[i] = alpha;
        Y0[i] = ord;
    }
}

void Traitement::DifferencesDivisees(int nb_point_interpole, QVector<double> tab_x, QVector<double> tab_fdx, double tab_result[NMAX][NMAX])
{
    int i, j;

    // Première itération : Xn = Yn
    for (i = 0; i <= nb_point_interpole; i++)
        tab_result[i][0] = tab_fdx[i];

    for (i = 1; i <= nb_point_interpole; i++)
        for (j = 0; j <= nb_point_interpole - i; j++)
            tab_result[j][i] = (tab_result[j + 1][i - 1] - tab_result[j][i - 1]) / (tab_x[j + i] - tab_x[j]);
}

double Traitement::Polynome(int nb_point_interpole, double tab_result[NMAX][NMAX], QVector<double> x, double alpha)
{
    int i;
    double val_polynome;
    val_polynome = tab_result[0][nb_point_interpole];
    for (i = 1; i <= nb_point_interpole; i++)
        val_polynome = val_polynome*(alpha - x[nb_point_interpole - i]) + tab_result[0][nb_point_interpole - i];
    return(val_polynome);
}

