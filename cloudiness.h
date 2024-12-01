#ifndef CLOUDINESS_H
#define CLOUDINESS_H

#include "sensor.h"

class Cloudiness : public Sensor
{
public:
    Cloudiness(int id, double reliability, const QString& name, double max, double min)
        : Sensor(id, "Nuvolosita", reliability, name, max, min){}

    void accept(SensorVisitor& visitor) override;

    QString getCloudinessLevel(double cloudDensity) const;
};

#endif // CLOUDINESS_H
