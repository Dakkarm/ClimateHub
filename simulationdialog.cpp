#include "simulationdialog.h"
#include "GUI/chartmanager.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

SimulationDialog::SimulationDialog(int numMeasurements, std::shared_ptr<Sensor> sensor, QWidget *parent)
    : QDialog(parent), numMeasurements(numMeasurements), sensor(sensor) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel(QString("Numero di misurazioni: %1").arg(numMeasurements), this);
    layout->addWidget(label);

    displaySensorInfo();

    if (sensor) {
        ChartManager* chartManager = new ChartManager(numMeasurements, sensor->getMin(), sensor->getMax(), sensor->getReliability());
        QChartView* chartView = chartManager->getChartView();
        layout->addWidget(chartView);
    }

    this->resize(750, 500);
}

void SimulationDialog::displaySensorInfo() {
    if (sensor) {
        qDebug() << "Numero di misurazioni:" << numMeasurements;
        qDebug() << "Min:" << sensor->getMin();
        qDebug() << "Max:" << sensor->getMax();
        qDebug() << "AffidabilitÃ :" << sensor->getReliability();
    } else {
        qDebug() << "Sensore non trovato!";
    }
}
