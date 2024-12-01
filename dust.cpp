#include "dust.h"
#include "sensorvisitor.h"

QString Dust::getDustLevelDescription() const {
    double avgValue = (getMax() + getMin()) / 2.0;
    if (avgValue < 10) {
        return "Low Dust Level";
    } else if (avgValue < 50) {
        return "Moderate Dust Level";
    } else {
        return "High Dust Level";
    }
}

void Dust::accept(SensorVisitor &visitor) {
    visitor.visit(*this);
}
