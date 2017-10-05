#include "principal.h"

Principal::Principal(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(afficherPoint(QCPAbstractPlottable*,int,QMouseEvent*)));
    connect(tabValeur, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(majPoint(QTableWidgetItem*)));

    traitement.calcul();
    makePlot();

    // initialise tabValeur
    tabValeur->setHorizontalHeaderLabels(QStringList({"x", "f(x)"}));
    tabValeur->blockSignals(true);
    for(int i=0; i<5; i++)
    {
        tabValeur->setItem(i,0,new QTableWidgetItem(QString::number(traitement.X1[i])));
        tabValeur->setItem(i,1,new QTableWidgetItem(QString::number(traitement.Y1[i])));
    }
    tabValeur->blockSignals(false);
}

void Principal::majPoint(QTableWidgetItem *item)
{
    qDebug() << "[col=" << item->column() << " row=" << item->row() << "] Valeur : " << item->text().toDouble();

     if(item->column() == 0)
        traitement.X1[item->row()] = item->text().toDouble();
    if(item->column() == 1)
        traitement.Y1[item->row()] = item->text().toDouble();

    etiquette->setVisible(false);
    fleche->setVisible(false);
    traitement.calcul();
    makePlot();
    customPlot->replot();
}

void Principal::afficherPoint(QCPAbstractPlottable *courbe, int, QMouseEvent *event)
{
    double x = customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = customPlot->yAxis->pixelToCoord(event->pos().y());

    qDebug() << courbe->name() << "x = " << x << " y = " << y;

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

