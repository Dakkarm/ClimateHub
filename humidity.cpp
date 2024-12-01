#include "humidity.h"
#include "sensorvisitor.h"


double Humidity::calculateDewPoint() const {
    double humidity = (getMax() + getMin()) / 2.0;
    double tempCelsius = 20.0;
    double dewPoint = tempCelsius - ((100 - humidity) / 5.0);
    return dewPoint;
}

void Humidity::accept(SensorVisitor &visitor) {
    visitor.visit(*this);
}
