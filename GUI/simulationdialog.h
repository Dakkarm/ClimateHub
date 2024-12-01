#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include <memory>
#include "sensor.h"

class SimulationDialog : public QDialog {
    Q_OBJECT

public:
    SimulationDialog(int numMeasurements, std::shared_ptr<Sensor> sensor, QWidget *parent = nullptr);

private:
    int numMeasurements;
    std::shared_ptr<Sensor> sensor;

    void displaySensorInfo();
};

#endif // SIMULATIONDIALOG_H
