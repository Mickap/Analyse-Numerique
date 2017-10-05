/** Analyse Numérique : Interpolation polynomiale via la méthode de Newton
  * Réalisé par : SOULENQ Joévin, ENJALBERT Bastien, PERIES Mickael
  * Basé sur les travaux de Jean BEUNEU : http://www.polytech-lille.fr/cours-algos-calcul-scientifique/
*/

#include "principal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Principal w;
    w.show();

    return a.exec();
}
