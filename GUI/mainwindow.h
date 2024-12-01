#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "ManagerSensor.h"

#include <QtCore>
#include <QtGui>

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QListWidget>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void open();
    void save();
    void exit();

private slots:
    void createLayout();
    void addSensor();
    void editSensor();
    void deleteSensor();
    void simulateSensor();
    void showSensorInfo();

    void filterSensorList(const QString &searchText);

private:
    QPushButton *createChartButton;
    QWidget *centralWidget;
    QVBoxLayout *layout;

    QListWidget *sensorList;
    ManagerSensor sensorManager;

    QAction *exitButton;
    QAction *saveButton;
    QAction *openButton;
    QLabel *sensorInfoLabel;
};

#endif // MAINWINDOW_H
