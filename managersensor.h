#ifndef MANAGERSENSOR_H
#define MANAGERSENSOR_H

#include <vector>
#include <memory>
#include "sensor.h"

class ManagerSensor {
public:
    void addSensor(std::shared_ptr<Sensor> sensor);
    std::vector<std::shared_ptr<Sensor>> getSensors() const;
    std::shared_ptr<Sensor> getSensorById(int id);
    void updateSensor(std::shared_ptr<Sensor> sensor);
    void removeSensor(int id);

private:
    std::vector<std::shared_ptr<Sensor>> sensors;
};

#endif // MANAGERSENSOR_H
