#include "principal.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    connect(graphique, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(afficherPoint(QCPAbstractPlottable*,int,QMouseEvent*)));
    connect(btnCalculer, SIGNAL(clicked(bool)), this, SLOT(calculerPoints(bool)));
    connect(choixCourbe, SIGNAL(currentTextChanged(QString)), this, SLOT(tracerCourbeInitiale(QString)));

    graphique->addGraph(); graphique->addGraph(); graphique->addGraph(); // on crée les trois graphiques
    makePlot();
}

void Principal::tracerCourbeInitiale(QString nomFonction)
{
    traitement.calculerCourbeInitiale(nomFonction);
    makePlot();
}

void Principal::calculerPoints(bool)
{
    etiquette->setVisible(false);
    fleche->setVisible(false);
    traitement.calculerCourbeInitiale(choixCourbe->currentText());
    traitement.calculerPointsInitiaux(inputNbPoints->value(), inputRandom->isChecked());
    traitement.calculNewton(inputPas->value());
    barreEtat->showMessage(QString::number(traitement.Xselec.size()) + " points interpôlés en " + QString::number(traitement.Xinterp.size()) + " points");
    makePlot();
}

void Principal::afficherPoint(QCPAbstractPlottable *courbe, int, QMouseEvent *event)
{
    double x = graphique->xAxis->pixelToCoord(event->pos().x());
    double y = graphique->yAxis->pixelToCoord(event->pos().y());

    qDebug().nospace() << courbe->name() << " x=" << x << " y=" << y;

    etiquette->setText("Coordonnées : x="+QString::number(x, 10, 2) + " y=" + QString::number(y, 10, 2));
    etiquette->setVisible(true);
    fleche->start->setParentAnchor(etiquette->bottom);
    fleche->end->setCoords(x, y);
    fleche->setVisible(true);
    graphique->replot();
}


void Principal::makePlot()
{
    // ajoute trois courbes
    graphique->graph(0)->setPen(QPen(Qt::green)); // couleur bleu pour fonction initiale
    graphique->graph(1)->setPen(QPen(Qt::red)); // couleur rouge pour les points
    graphique->graph(1)->setLineStyle(QCPGraph::lsNone); // affiche uniquement les points
    graphique->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8)); // les points sont en forme de cercle de rayon 8px
    graphique->graph(2)->setPen(QPen(Qt::blue)); // couleur bleu pour la fonction interpolée

    // ajoute une légende
    graphique->legend->setVisible(true);
    // customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop); Mettre la légende à gauche
    graphique->graph(0)->setName("Fonction initiale");
    graphique->graph(1)->setName("Points sélectionnés");
    graphique->graph(2)->setName("Fonction interpolée");

    // envoie les données au graphique
    graphique->graph(0)->setData(traitement.Xinit, traitement.Yinit);
    graphique->graph(1)->setData(traitement.Xselec, traitement.Yselec);
    graphique->graph(2)->setData(traitement.Xinterp, traitement.Yinterp);

    // Redimensionne les axes
    graphique->rescaleAxes();

    // Permet de scroller avec la souris, zoomer avec la molette et de sélectionner les graphiques
    graphique->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // ajoute un label
    etiquette = new QCPItemText(graphique);
    etiquette->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    etiquette->position->setType(QCPItemPosition::ptAxisRectRatio);
    etiquette->position->setCoords(0.5, 0); // place en haut au milieu
    etiquette->setFont(QFont(font().family(), 16)); // fonte plus épaisse
    etiquette->setPen(QPen(Qt::black)); // bordure noire
    etiquette->setVisible(false);

    // ajoute une flèche
    fleche = new QCPItemLine(graphique);
    fleche->setHead(QCPLineEnding::esSpikeArrow);
    fleche->setVisible(false);

    // ré-actualise l'affichage
    graphique->replot();
}

