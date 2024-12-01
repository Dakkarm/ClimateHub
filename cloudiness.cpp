#include "cloudiness.h"
#include "sensorvisitor.h"

void Cloudiness::accept(SensorVisitor &visitor) {
    visitor.visit(*this);
}

QString Cloudiness::getCloudinessLevel(double cloudDensity) const {
    if (cloudDensity >= 75.0) {
        return "Alto";
    } else if (cloudDensity >= 30.0) {
        return "Moderato";
    } else {
        return "Basso";
    }
}
