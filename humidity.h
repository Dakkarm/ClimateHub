#ifndef HUMIDITY_H
#define HUMIDITY_H

#include "sensor.h"

class Humidity : public Sensor {
public:
    Humidity(int id, double reliability, const QString& name, double max, double min)
        : Sensor(id, "Umidita", reliability, name, max, min){}

    void accept(SensorVisitor& visitor) override;

    double calculateDewPoint() const;
};

#endif // HUMIDITY_H

