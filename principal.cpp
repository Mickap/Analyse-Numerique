#include "principal.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(afficherPoint(QCPAbstractPlottable*,int,QMouseEvent*)));
    connect(btnCalculer, SIGNAL(clicked(bool)), this, SLOT(calculerPoints(bool)));
    connect(btnAjout, SIGNAL(clicked(bool)), this, SLOT(ajoutPoint(bool)));
    connect(btnSuppr, SIGNAL(clicked(bool)), this, SLOT(supprPoint(bool)));

    tabValeur->setHorizontalHeaderLabels(QStringList({"x", "f(x)"}));    
    makePlot();
}

void Principal::calculerPoints(bool)
{
    int n = tabValeur->rowCount();
    traitement.nb_points = n;
    traitement.X1.resize(n);
    traitement.Y1.resize(n);

    // récupère les valeurs du tableau pour les placer dans X1 et Y1
    for(int i=0; i < n; i++)
    {
        traitement.X1[i] = tabValeur->item(i,0)->text().toDouble();
        traitement.Y1[i] = tabValeur->item(i,1)->text().toDouble();
    }

    etiquette->setVisible(false);
    fleche->setVisible(false);
    traitement.pas = inputPas->value();
    traitement.calculNewton();
    makePlot();
    customPlot->replot();
}

void Principal::ajoutPoint(bool)
{
    tabValeur->insertRow(tabValeur->rowCount());
}

void Principal::supprPoint(bool)
{
    tabValeur->removeRow(tabValeur->rowCount()-1);
}

void Principal::afficherPoint(QCPAbstractPlottable *courbe, int, QMouseEvent *event)
{
    double x = customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = customPlot->yAxis->pixelToCoord(event->pos().y());

    qDebug().nospace() << courbe->name() << " x=" << x << " y=" << y;

    etiquette->setText("Coordonnées : x="+QString::number(x, 10, 2) + " y=" + QString::number(y, 10, 2));
    etiquette->setVisible(true);
    fleche->start->setParentAnchor(etiquette->bottom);
    fleche->end->setCoords(x, y);
    fleche->setVisible(true);
    customPlot->replot();
}

void Principal::makePlot()
{
    // ajoute deux courbes
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // couleur bleu pour la premier courbe
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red)); // couleur rouge pour la premier courbe
    customPlot->graph(1)->setLineStyle(QCPGraph::lsNone); // affiche uniquement les points
    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8)); // les points sont en forme de cercle de rayon 8px

    // envoie les données au graphique
    customPlot->graph(0)->setData(traitement.X0, traitement.Y0);
    customPlot->graph(1)->setData(traitement.X1, traitement.Y1);

    // Redimensionne les axes
    customPlot->rescaleAxes();

    // Permet de scroller avec la souris, zoomer avec la molette et de sélectionner les graphiques
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // ajoute un label
    etiquette = new QCPItemText(customPlot);
    etiquette->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    etiquette->position->setType(QCPItemPosition::ptAxisRectRatio);
    etiquette->position->setCoords(0.5, 0); // place en haut au milieu
    etiquette->setFont(QFont(font().family(), 16)); // fonte plus épaisse
    etiquette->setPen(QPen(Qt::black)); // bordure noire
    etiquette->setVisible(false);

    // ajoute une flèche
    fleche = new QCPItemLine(customPlot);
    fleche->setHead(QCPLineEnding::esSpikeArrow);
    fleche->setVisible(false);
}

