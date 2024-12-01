#ifndef DUST_H
#define DUST_H

#include "sensor.h"

class Dust : public Sensor {
public:
    Dust(int id, double reliability, const QString& name, double max, double min)
        : Sensor(id, "Polvere", reliability, name, max, min){}

    void accept(SensorVisitor& visitor) override;

    QString getDustLevelDescription() const;
};

#endif // DUST_H
