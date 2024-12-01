#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "sensor.h"

class Temperature : public Sensor {
public:

    Temperature(int id, double reliability, const QString& name, double max, double min)
        : Sensor(id, "Temperatura", reliability, name, max, min){}

    void accept(SensorVisitor& visitor) override;
};
#endif // TEMPERATURE_H
