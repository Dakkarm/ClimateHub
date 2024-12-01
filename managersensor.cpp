#include <QDebug>
#include "managersensor.h"

void ManagerSensor::addSensor(std::shared_ptr<Sensor> sensor) {
    sensors.push_back(sensor);
}

std::vector<std::shared_ptr<Sensor>> ManagerSensor::getSensors() const {
    return sensors;
}

std::shared_ptr<Sensor> ManagerSensor::getSensorById(int id) {
    for (const auto& sensor : sensors) {
        if (sensor->getId() == id) {
            return sensor;
        }
    }
    return nullptr;
}

void ManagerSensor::updateSensor(std::shared_ptr<Sensor> sensor) {
    for (auto& existingSensor : sensors) {
        if (existingSensor->getId() == sensor->getId()) {
            existingSensor = sensor;
            return;
        }
    }
}

void ManagerSensor::removeSensor(int id) {
    sensors.erase(
        std::remove_if(sensors.begin(), sensors.end(), [id](const std::shared_ptr<Sensor>& sensor) {
            return sensor->getId() == id;
        }),
        sensors.end()
        );
}
