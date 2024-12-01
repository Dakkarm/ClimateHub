#include "sensor.h"

Sensor::Sensor(int id, const QString& type, double reliability, const QString& name, double max, double min)
    : id(id), type(type), reliability(reliability), name(name), max(max), min(min) {}

Sensor::~Sensor() {}

int Sensor::getId() const {
    return id;
}

QString Sensor::getType() const {
    return type;
}

double Sensor::getReliability() const {
    return reliability;
}

QString Sensor::getName() const {
    return name;
}

double Sensor::getMax() const {
    return max;
}

double Sensor::getMin() const {
    return min;
}

void Sensor::setName(const QString &newName) {
    name = newName;
}

void Sensor::setReliability(double newReliability) {
    reliability = newReliability;
}

void Sensor::setMax(double newMax) {
    max = newMax;
}

void Sensor::setMin(double newMin) {
    min = newMin;
}
