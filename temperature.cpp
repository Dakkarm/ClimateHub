#include "temperature.h"

#include "sensorvisitor.h"

void Temperature::accept(SensorVisitor &visitor) {
    visitor.visit(*this);
}

