#include "simulationvisitor.h"
#include "temperature.h"
#include "humidity.h"
#include "wind.h"
#include "dust.h"
#include "cloudiness.h"
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QToolTip>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

SimulationVisitor::SimulationVisitor(int numMeasurements)
    : numMeasurements(numMeasurements){}

void SimulationVisitor::visit(Dust& sensor) {
    createChartDust(sensor.getName(), "Dust simulation data", sensor.getMax(), sensor.getMin());
}

void SimulationVisitor::visit(Temperature& sensor) {

    createChartStyle2(sensor.getName(), "Temperature simulation data", sensor.getMax(), sensor.getMin());
}

void SimulationVisitor::visit(Wind& sensor) {

    createChartStyle2(sensor.getName(), "Wind simulation data", sensor.getMax(), sensor.getMin());
}

void SimulationVisitor::visit(Humidity& sensor) {

    createChart(sensor.getName(), "Humidity simulation data", sensor.getMax(), sensor.getMin());
}

void SimulationVisitor::visit(Cloudiness& sensor) {

    createChart(sensor.getName(), "Cloudiness simulation data", sensor.getMax(), sensor.getMin());
}

void SimulationVisitor::createChartDust(const QString& title, const QString& description, double maxValue, double minValue) {

    QChart *chart = new QChart();
    chart->setTitle(title);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QScatterSeries *seriesLow = new QScatterSeries();
    seriesLow->setName("Basso");
    seriesLow->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    seriesLow->setMarkerSize(8.0);
    seriesLow->setColor(QColorConstants::Svg::orange);

    QScatterSeries *seriesMid = new QScatterSeries();
    seriesMid->setName("Medio");
    seriesMid->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    seriesMid->setMarkerSize(8.0);
    seriesMid->setColor(Qt::red);

    QScatterSeries *seriesHigh = new QScatterSeries();
    seriesHigh->setName("Alto");
    seriesHigh->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    seriesHigh->setMarkerSize(8.0);
    seriesHigh->setColor(QColorConstants::Svg::purple);

    QList<QPointF> coordinates = generateRandomCoordinates(numMeasurements, minValue, maxValue);
    for (const QPointF& point : coordinates) {
        if (point.y() < (minValue + (maxValue - minValue) / 3)) {
            seriesLow->append(point);
        } else if (point.y() < (minValue + 2 * (maxValue - minValue) / 3)) {
            seriesMid->append(point);
        } else {
            seriesHigh->append(point);
        }
    }

    chart->addSeries(seriesLow);
    chart->addSeries(seriesMid);
    chart->addSeries(seriesHigh);

    QCategoryAxis *xAxis = new QCategoryAxis();
    for (int i = 0; i <= numMeasurements; i += numMeasurements / 5) {
        xAxis->append(QString::number(i), i);
    }
    xAxis->setRange(0, numMeasurements - 1);
    xAxis->setTitleText("Misurazioni");
    chart->addAxis(xAxis, Qt::AlignBottom);
    seriesLow->attachAxis(xAxis);
    seriesMid->attachAxis(xAxis);
    seriesHigh->attachAxis(xAxis);

    QValueAxis *yAxis = new QValueAxis();
    yAxis->setGridLineVisible(true);
    yAxis->setLabelFormat("%.1f");
    yAxis->setRange(minValue, maxValue);
    yAxis->setTitleText(description);
    chart->addAxis(yAxis, Qt::AlignLeft);
    seriesLow->attachAxis(yAxis);
    seriesMid->attachAxis(yAxis);
    seriesHigh->attachAxis(yAxis);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Aggiungi pulsanti di controllo dello zoom
    QPushButton *zoomInButton = new QPushButton("Zoom In");
    QPushButton *zoomOutButton = new QPushButton("Zoom Out");
    QPushButton *resetZoomButton = new QPushButton("Reset Zoom");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);
    buttonLayout->addWidget(resetZoomButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addLayout(buttonLayout);

    QWidget *container = new QWidget;
    container->setLayout(layout);
    container->resize(1000, 650);
    container->show();


    // Imposta zoom iniziale al 90%
    chart->zoom(0.9);

    // Funzioni di controllo per zoom
    QObject::connect(zoomInButton, &QPushButton::clicked, container, [chart]() {
        chart->zoomIn();
    });

    QObject::connect(zoomOutButton, &QPushButton::clicked, container, [chart]() {
        chart->zoomOut();
    });

    QObject::connect(resetZoomButton, &QPushButton::clicked, container, [chart]() {
        chart->zoomReset();
        chart->zoom(0.9);
    });


    // Modifica dello sfondo del grafico
    chart->setBackgroundBrush(QBrush(QColor(245, 245, 245)));
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::white));
    chart->setPlotAreaBackgroundVisible(true);

    // Modifica dello stile delle linee della griglia
    QPen gridPen(Qt::gray);
    gridPen.setStyle(Qt::DashLine);
    yAxis->setGridLinePen(gridPen);
    xAxis->setGridLinePen(gridPen);

    // Abilita animazioni per l'inserimento e l'aggiornamento delle serie di dati
    chart->setAnimationOptions(QChart::SeriesAnimations);
}


/*

void SimulationVisitor::createChart(const QString& title, const QString& description, double maxValue, double minValue) {
    QLineSeries *series = new QLineSeries();

    // Genera i punti casuali
    QList<QPointF> coordinates = generateRandomCoordinates(numMeasurements, minValue, maxValue);

    // Aggiungi i punti alla serie
    for (const QPointF& point : coordinates) {
        series->append(point);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);

    QPen pen(Qt::blue);
    pen.setWidth(2);
    pen.setColor(QColor(70, 130, 180, 150));  // Colore blu con trasparenza
    series->setPen(pen);

    series->setPointsVisible(true);
    series->setMarkerSize(6.0);

    // Aggiunta di tooltip per mostrare i dettagli del punto al passaggio del mouse
    QObject::connect(series, &QLineSeries::hovered, [=](const QPointF &point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(), QString("X: %1, Y: %2").arg(point.x()).arg(point.y()));
        }
    });

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //chartView->setInteractive(true);  // Abilita l'interattività (zoom, pan)
    chartView->resize(800, 600);
    chartView->show();

    QValueAxis *yAxis = new QValueAxis();
    yAxis->setRange(minValue, maxValue);
    yAxis->setTitleText(description);
    yAxis->setGridLineVisible(true);  // Mostra le linee della griglia per l'asse Y
    yAxis->setLabelFormat("%.1f");    // Formatta le etichette dell'asse Y
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    QCategoryAxis *xAxis = new QCategoryAxis();
    for (int i = 0; i <= numMeasurements; i += numMeasurements / 5) {
        xAxis->append(QString::number(i), i);
    }
    xAxis->setRange(0, numMeasurements - 1);
    xAxis->setTitleText("Misurazioni");
    xAxis->setLabelsAngle(-45);  // Ruota le etichette dell'asse X per migliorarne la leggibilità
    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);

    // Abilita animazioni per l'inserimento e l'aggiornamento delle serie di dati
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Modifica dei margini e padding per un migliore utilizzo dello spazio
    chart->setMargins(QMargins(10, 10, 10, 10));      // Imposta margini interni del grafico

    // Modifica dello sfondo del grafico
    chart->setBackgroundBrush(QBrush(QColor(245, 245, 245)));  // Imposta uno sfondo grigio chiaro
    chart->setPlotAreaBackgroundBrush(QBrush(Qt::white));      // Imposta uno sfondo bianco per l'area del grafico
    chart->setPlotAreaBackgroundVisible(true);                 // Rende visibile lo sfondo dell'area del grafico

    // Modifica dello stile delle linee della griglia
    QPen gridPen(Qt::gray);
    gridPen.setStyle(Qt::DashLine);               // Stile tratteggiato per le linee della griglia
    yAxis->setGridLinePen(gridPen);               // Applica il nuovo stile all'asse Y
    xAxis->setGridLinePen(gridPen);               // Applica il nuovo stile all'asse X

    // Aggiunta di una linea di soglia orizzontale per indicare un valore di riferimento
    QLineSeries *thresholdSeries = new QLineSeries();
    thresholdSeries->append(0, (maxValue + minValue) / 2);
    thresholdSeries->append(numMeasurements - 1, (maxValue + minValue) / 2);
    QPen thresholdPen(Qt::red);
    thresholdPen.setWidth(2);
    thresholdPen.setStyle(Qt::DashDotLine);       // Stile tratto-punto per la linea di soglia
    thresholdSeries->setPen(thresholdPen);
    chart->addSeries(thresholdSeries);            // Aggiunge la linea di soglia al grafico
    thresholdSeries->attachAxis(xAxis);
    thresholdSeries->attachAxis(yAxis);

    // Aggiunta di zoom tramite rotellina del mouse
    chartView->setRubberBand(QChartView::RectangleRubberBand); // Abilita il disegno di una selezione per il zoom

    // Aggiunta di un cursore personalizzato per le operazioni di pan
    //chartView->setCursor(Qt::OpenHandCursor);     // Imposta il cursore a "mano aperta"
}


*/





void SimulationVisitor::createChartStyle2(const QString& title, const QString& description, double maxValue, double minValue) {
    QLineSeries *series = new QLineSeries();

    // Genera i punti casuali
    QList<QPointF> coordinates = generateRandomCoordinates(numMeasurements, minValue, maxValue);

    // Aggiungi i punti alla serie
    for (const QPointF& point : coordinates) {
        series->append(point);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle(title);

    QPen pen(Qt::red);

    // Stile Linea
    pen.setWidth(2);
    series->setPen(pen);

    // Stile Punti
    series->setPointsVisible(true);
    series->setMarkerSize(5.0);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(800, 600);
    chartView->show();

    QValueAxis *yAxis = new QValueAxis();
    yAxis->setRange(minValue, maxValue);
    yAxis->setTitleText(description);
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);

    QCategoryAxis *xAxis = new QCategoryAxis();
    for (int i = 0; i <= numMeasurements; i += numMeasurements / 5) {
        xAxis->append(QString::number(i), i);
    }
    xAxis->setRange(0, numMeasurements - 1);
    xAxis->setTitleText("Misurazioni");
    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);
}


QList<QPointF> SimulationVisitor::generateRandomCoordinates(int numMeasurements, double minValue, double maxValue) {
    QList<QPointF> coordinates;

    // Genera i valori casuali
    for (int i = 0; i < numMeasurements; ++i) {
        double randomValue = minValue + (maxValue - minValue) * QRandomGenerator::global()->generateDouble();
        coordinates.append(QPointF(i, randomValue));
    }

    // Imposta minValue e maxValue
    if (numMeasurements >= 2) {
        int index1 = QRandomGenerator::global()->bounded(numMeasurements);
        int index2;
        do {
            index2 = QRandomGenerator::global()->bounded(numMeasurements);
        } while (index1 == index2);

        coordinates[index1].setY(minValue);
        coordinates[index2].setY(maxValue);
    }

    return coordinates;
}

