#include "wind.h"
#include "sensorvisitor.h"

double Wind::calculateWindChill() const {
    double temperature = 10.0;
    double windSpeed = (getMax() + getMin()) / 2.0;
    double windChill = 13.12 + 0.6215 * temperature - 11.37 * pow(windSpeed, 0.16) + 0.3965 * temperature * pow(windSpeed, 0.16);
    return windChill;
}

void Wind::accept(SensorVisitor &visitor) {
    visitor.visit(*this);
}
