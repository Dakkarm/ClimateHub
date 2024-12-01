#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

class Temperature;
class Dust;
class Humidity;
class Wind;
class Cloudiness;

class SensorVisitor {
public:
    virtual void visit(Temperature& temperature) = 0;
    virtual void visit(Dust& dust) = 0;
    virtual void visit(Humidity& humidity) = 0;
    virtual void visit(Wind& wind) = 0;
    virtual void visit(Cloudiness& cloudiness) = 0;
};

#endif // SENSORVISITOR_H
