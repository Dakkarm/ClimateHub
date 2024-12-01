#ifndef SENSORINPUTDIALOG_H
#define SENSORINPUTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDoubleSpinBox>

class SensorInputDialog : public QDialog {
    Q_OBJECT

public:
    SensorInputDialog(QWidget *parent = nullptr);
    QString getType() const;
    int getId() const;
    QString getName() const;
    double getReliability() const;
    double getMax() const;
    double getMin() const;

    void setType(const QString &type);
    void setId(int id);
    void setName(const QString &name);
    void setReliability(double reliability);
    void setMax(double max);
    void setMin(double min);

    void disableTypeSelection();
    //void disableIdSelection();

    void applyStyle();

private:
    void createLayout();
    QComboBox *typeComboBox;
    QSpinBox *idSpinBox;
    QLineEdit *nameLineEdit;
    QDoubleSpinBox *reliabilitySpinBox;
    QDoubleSpinBox *maxSpinBox;
    QDoubleSpinBox *minSpinBox;
};

#endif // SENSORINPUTDIALOG_H
