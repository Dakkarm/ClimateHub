#ifndef SENSOR_H
#define SENSOR_H

#include <QString>

class SensorVisitor;

class Sensor {
public:
    Sensor(int id, const QString& type, double reliability, const QString& name, double max, double min);

    virtual ~Sensor();

    int getId() const;
    QString getType() const;
    double getReliability() const;
    QString getName() const;
    double getMax() const;
    double getMin() const;

    void setName(const QString &newName);
    void setReliability(double newReliability);
    void setMax(double newMax);
    void setMin(double newMin);

    virtual void accept(SensorVisitor& visitor) = 0;

private:
    int id;
    QString type;
    double reliability;
    QString name;
    double max;
    double min;
};

#endif // SENSOR_H
