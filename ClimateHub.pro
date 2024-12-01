QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/mainwindow.cpp \
    GUI/sensorinputdialog.cpp \
    GUI/simulationvisitor.cpp \
    cloudiness.cpp \
    dust.cpp \
    humidity.cpp \
    main.cpp \
    managersensor.cpp \
    sensor.cpp \
    sensorvisitor.cpp \
    temperature.cpp \
    wind.cpp

HEADERS += \
    GUI/mainwindow.h \
    GUI/sensorinputdialog.h \
    GUI/simulationvisitor.h \
    cloudiness.h \
    dust.h \
    humidity.h \
    managersensor.h \
    sensor.h \
    sensorvisitor.h \
    temperature.h \
    wind.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
