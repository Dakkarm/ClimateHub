#ifndef WIND_H
#define WIND_H

#include "sensor.h"

class Wind : public Sensor {
public:
    Wind(int id, double reliability, const QString& name, double max, double min)
        : Sensor(id, "Vento", reliability, name, max, min){}

    void accept(SensorVisitor& visitor) override;

    double calculateWindChill() const;

};
#endif // WIND_H
