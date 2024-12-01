#ifndef SIMULATION_VISITOR_H
#define SIMULATION_VISITOR_H

#include "sensorvisitor.h"
#include "dust.h"
#include "temperature.h"
#include "wind.h"
#include "humidity.h"
#include "cloudiness.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class SimulationVisitor : public SensorVisitor {
public:
    SimulationVisitor(int numMeasurements);

    void visit(Dust& sensor) override;
    void visit(Temperature& sensor) override;
    void visit(Wind& sensor) override;
    void visit(Humidity& sensor) override;
    void visit(Cloudiness& sensor) override;

    void createChart(const QString& title, const QString& description, double minValue, double maxValue);
    void createChartStyle2(const QString& title, const QString& description, double minValue, double maxValue);

    QList<QPointF> generateRandomCoordinates(int numMeasurements, double minValue, double maxValue);

private:
    int numMeasurements;
};

#endif // SIMULATION_VISITOR_H
