#include "traitement.h"

/**
 * @brief Traitement::calculNewton
 * @param pas : corresponds à l'intervale entre chaque valeur de x à interpoler
 */
void Traitement::calculNewton(double pas)
{
    QVector<QVector<double> > mat_diff_div; // tableau des différences divisés
    double y, x=min;            // contiendra chaque points du polynome
    nb_points = Xselec.size();  // nombre de points fournis
    int n=nb_points - 1;        // indice du dernier élément de X1


    qDebug() << "Calcul des différences divisées :";
    mat_diff_div = DifferencesDivisees();

    qDebug() << "Calcul du polynôme d'interpolation :";
    Xinterp.clear(); Yinterp.clear(); // on efface le tableau
    for (int i = 0; x <= max; x+=pas, i++) {

        // Calcul des points Xinterp d'interpolation
        Xinterp.append(x);

        // Calcul des points Yinterp d'interpolation
        y = mat_diff_div[0][n];
        for (int j = 1; j <= n; j++) {
            y = y * (Xinterp[i] - Xselec[n - j]) + mat_diff_div[0][n - j];
        }
        Yinterp.append(y);
    }
    qDebug() << "Xinterp :" << Xinterp << endl << "Yinterp :" << Yinterp << endl;
}

/**
 * @brief Traitement::DifferencesDivisees
 * @return tableau des différences divisées
 */
QVector<QVector<double> > Traitement::DifferencesDivisees()
{
    int i, j;
    QDebug debug = qDebug().noquote().nospace();
    QVector<QVector<double>> mat_diff_div(nb_points);
    for (i = 0; i < nb_points; ++i) mat_diff_div[i].resize(nb_points);

    // calcul du premier coefficient
    for (i = 0; i < nb_points; i++)
        mat_diff_div[i][0] = Yselec[i];

    // calcul de chaque colonne ligne à ligne
    for (i = 1; i < nb_points; i++)
        for (j = 0; j < nb_points - i; j++)
            mat_diff_div[j][i] = (mat_diff_div[j + 1][i - 1] - mat_diff_div[j][i - 1]) / (Xselec[j + i] - Xselec[j]);


    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 4 - i; j++) {
            if(mat_diff_div[i][j]>0) debug << " +" << QString::number(mat_diff_div[i][j], 'f', 4);
            else                     debug << ' '  << QString::number(mat_diff_div[i][j], 'f', 4);
        }
        debug << endl;
    }

    return mat_diff_div;
}

/**
 * @brief Traitement::calculerCourbeInitiale crée une fonction initiale "parfaite" (Xinit, Yinit) que l'on comparera avec la courbe interpolée
 * @param nomFonction : nom de la fonction à tracer
 */
void Traitement::calculerCourbeInitiale(QString nomFonction)
{
    min=0.0;         // valeur minimum
    max=10.0;        // valeur maximum
    double pas=0.01; // précision

    // réglages spécifiques pour certaines fonctions
    if(nomFonction == "sin(x)") max = 2*M_PI;
    if(nomFonction == "cos(x)") max = 2*M_PI;
    if(nomFonction == "1/x")  { min = 0.01; max = 5.0; }
    if(nomFonction == "x²")     min = -10.0;
    if(nomFonction == "x³")     min = -10.0;
    if(nomFonction == "log(x)") min = 0.01;

    Xinit.clear(); Yinit.clear(); // on efface le tableau
    for(double i=min; i <= max; i+=pas) {
        Xinit.append(i);
        if(nomFonction == "sin(x)") Yinit.append(sin(i*2));
        if(nomFonction == "cos(x)") Yinit.append(cos(i*2));
        if(nomFonction == "1/x")    Yinit.append(1/i);
        if(nomFonction == "x²")     Yinit.append(pow(i, 2));
        if(nomFonction == "x³")     Yinit.append(pow(i, 3));
        if(nomFonction == "√x")     Yinit.append(sqrt(i));
        if(nomFonction == "log(x)") Yinit.append(log(i));
        if(nomFonction == "exp(x)") Yinit.append(exp(i));
    }
}

/**
 * @brief Traitement::calculerPointsInitiaux
 * @param nbPointsInterp : nombre de points à extraire de la fonction initiale (Xinit/Yinit)
 * @param randomActive : active ou non la sélection des points de manière aléatoire
 */
void Traitement::calculerPointsInitiaux(int nbPointsInterp, bool randomActive)
{
    int i;
    Xselec.clear(); Yselec.clear(); // on efface le tableau

    // On place un point au début de la courbe
    Xselec.append(Xinit.first());
    Yselec.append(Yinit.first());

    // Sélection des points à intervalle aléatoire
    if(randomActive) {
        nbPointsInterp-=2;
        QStringList list_random;
        int random=0;
        for (i = 0; i < nbPointsInterp; i++) {
            do  {
                random = rand() % (Xinit.size() / nbPointsInterp) + (Xinit.size() / nbPointsInterp) * i;
            } while(list_random.contains(QString::number(random))
                    || list_random.contains(QString::number(random-1))
                    || list_random.contains(QString::number(random-2))
                    || list_random.contains(QString::number(random+1))
                    || list_random.contains(QString::number(random+2)));

            list_random.append(QString::number(random));
            Xselec.append(Xinit[random]);
            Yselec.append(Yinit[random]);
        }
    }

    // Sélection des points à intervalle régulier
    else {
        nbPointsInterp--;
        for (i = 1; i < nbPointsInterp; i++) {
            Xselec.append(Xinit[(i*Xinit.size()/nbPointsInterp)]);
            Yselec.append(Yinit[(i*Xinit.size()/nbPointsInterp)]);
        }
    }

    // On place un point à la fin de la courbe
    Xselec.append(Xinit.last());
    Yselec.append(Yinit.last());

    qDebug() << "Xselec :" << Xselec << endl << "Yselec :" << Yselec << endl;
}

/**
 * @brief Traitement::calculerResidus calcule la somme des résidus au carré
 * @return somme des résidus au carré
 */
double Traitement::calculerResidus()
{
    double residus = 0.0;

    for(int i=0; i < Xinit.size(); i++)
        for(int j=0; j < Xinterp.size(); j++)
                if(trunc(Xinit[i]*100) == trunc(Xinterp[j]*100)) // compare avec une précision de 0.01
                    residus += pow((Yinit[i] - Yinterp[j]), 2);

    qDebug().noquote() << "SRC : " << QString::number(residus, 'g');
    return residus;
}
