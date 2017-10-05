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

void Traitement::DifferencesDivisees(int n, QVector<double> x, QVector<double> f, double d[NMAX][NMAX])
{
    int i, j;
    for (j = 0; j <= n; j++)
        d[j][0] = f[j];
    for (j = 1; j <= n; j++)
        for (i = 0; i <= n - j; i++)
            d[i][j] = (d[i + 1][j - 1] - d[i][j - 1]) / (x[i + j] - x[i]);
}

double Traitement::Polynome(int n, double d[NMAX][NMAX], QVector<double> x, double alpha)
{
    int i;
    double p;
    p = d[0][n];
    for (i = 1; i <= n; i++)
        p = p*(alpha - x[n - i]) + d[0][n - i];
    return(p);
}

