#include "mainwindow.h"
#include "simulationvisitor.h"
#include "sensorinputdialog.h"
#include "dust.h"
#include "temperature.h"
#include "wind.h"
#include "humidity.h"
#include "cloudiness.h"

#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sensorList(new QListWidget(this)) {

    setWindowTitle("ClimateHub");
    setFixedSize(600, 900);

    // Icona
    QPixmap pixmap(":/Images/logo.png");
    QSize iconSize(200, 200);
    pixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio);
    setWindowIcon(QIcon(pixmap));

    // Background
    QString globalStyleSheet = "background-color: #87CEEB;";
    setStyleSheet(globalStyleSheet);

    createLayout();
}

void MainWindow::createLayout() {

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QMenuBar *menuBar = new QMenuBar(this);

    // Menu File
    QIcon menuLogo(":/Images/menu.png");
    QMenu *fileMenu = menuBar->addMenu(menuLogo, tr(" "));

    QIcon openLogo(":/Images/open.png");
    openButton = fileMenu->addAction(openLogo, tr("Apri"));
    openButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    QIcon saveLogo(":/Images/save.png");
    saveButton = fileMenu->addAction(saveLogo, tr("Salva"));
    saveButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    fileMenu->addSeparator();
    QIcon exitLogo(":/Images/exit.png");
    exitButton = fileMenu->addAction(exitLogo, tr("Exit"));

    // Stile menu
    menuBar->setStyleSheet("QMenuBar { background-color: #FFA500; color: white; }"
                           "QMenuBar::item { background-color: #FFA500; color: white; }"
                           "QMenuBar::item:selected { background-color: #E59400; }"
                           "QMenu { background-color: #E59400; color: white; }"
                           "QMenu::item { background-color: #E59400; color: white; }"
                           "QMenu::item:selected { background-color: #CC8400; }");

    connect(openButton, &QAction::triggered, this, &MainWindow::open);
    connect(saveButton, &QAction::triggered, this, &MainWindow::save);
    connect(exitButton, &QAction::triggered, this, &MainWindow::exit);

    mainLayout->setMenuBar(menuBar);

    // Layout centrale
    QVBoxLayout *centralLayout = new QVBoxLayout();

    // Filtro
    QLineEdit *searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca sensori...");
    searchBar->setStyleSheet("padding: 10px; font-size: 16px;");
    centralLayout->addWidget(searchBar);

    sensorList->setFixedWidth(300);
    centralLayout->addWidget(sensorList);

    sensorInfoLabel = new QLabel(this);
    sensorInfoLabel->setStyleSheet("background-color: white; color: black; padding: 10px; border: 1px solid #999; border-radius: 5px;");
    mainLayout->addWidget(sensorInfoLabel);

    connect(sensorList, &QListWidget::itemSelectionChanged, this, &MainWindow::showSensorInfo);

    mainLayout->addLayout(centralLayout);

    // Pulsanti
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    QHBoxLayout *firstRowLayout = new QHBoxLayout();
    QHBoxLayout *secondRowLayout = new QHBoxLayout();

    QPushButton *addButton = new QPushButton("Aggiungi", this);
    QPushButton *editButton = new QPushButton("Modifica", this);
    QPushButton *deleteButton = new QPushButton("Elimina", this);
    QPushButton *simulateButton = new QPushButton("Simula", this);

    QSize buttonSize(280, 70);

    addButton->setFixedSize(buttonSize);
    editButton->setFixedSize(buttonSize);
    deleteButton->setFixedSize(buttonSize);
    simulateButton->setFixedSize(buttonSize);

    firstRowLayout->addWidget(addButton);
    firstRowLayout->addWidget(editButton);
    secondRowLayout->addWidget(deleteButton);
    secondRowLayout->addWidget(simulateButton);

    buttonLayout->addLayout(firstRowLayout);
    buttonLayout->addLayout(secondRowLayout);

    mainLayout->addLayout(buttonLayout);

    // Stili dei pulsanti
    addButton->setStyleSheet("background-color: #32CD32; color: white; font-size: 18px;");
    editButton->setStyleSheet("background-color: #1E90FF; color: white; font-size: 18px;");
    deleteButton->setStyleSheet("background-color: #FF4500; color: white; font-size: 18px;");
    simulateButton->setStyleSheet("background-color: #FFD700; color: white; font-size: 18px;");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addSensor);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editSensor);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteSensor);
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::simulateSensor);

    setCentralWidget(centralWidget);

    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    buttonLayout->setSpacing(10);
    firstRowLayout->setSpacing(10);
    secondRowLayout->setSpacing(10);

    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::filterSensorList);
}

void MainWindow::filterSensorList(const QString &searchText) {
    for (int i = 0; i < sensorList->count(); ++i) {
        QListWidgetItem *item = sensorList->item(i);
        if (item->text().contains(searchText, Qt::CaseInsensitive)) {
            item->setHidden(false);
        } else {
            item->setHidden(true);
        }
    }
}

void MainWindow::addSensor() {
    SensorInputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString sensorType = dialog.getType();
        int id = dialog.getId();
        QString name = dialog.getName();
        double reliability = dialog.getReliability();
        double max = dialog.getMax();
        double min = dialog.getMin();

        if (max <= min) {
            QMessageBox::warning(this, "Errore", "Il valore massimo deve essere maggiore del valore minimo.");
            return;
        }

        std::shared_ptr<Sensor> sensor;

        if (sensorType == "Polvere") {
            sensor = std::make_shared<Dust>(id, reliability, name, max, min);
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/Images/dust.png"), sensor->getName());
            item->setData(Qt::UserRole, id);
            sensorList->addItem(item);
        } else if (sensorType == "Temperatura") {
            sensor = std::make_shared<Temperature>(id, reliability, name, max, min);
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/Images/temperature.png"), sensor->getName());
            item->setData(Qt::UserRole, id);
            sensorList->addItem(item);
        } else if (sensorType == "Umidita") {
            sensor = std::make_shared<Humidity>(id, reliability, name, max, min);
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/Images/humidity.png"), sensor->getName());
            item->setData(Qt::UserRole, id);
            sensorList->addItem(item);
        } else if (sensorType == "Vento") {
            sensor = std::make_shared<Wind>(id, reliability, name, max, min);
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/Images/wind.png"), sensor->getName());
            item->setData(Qt::UserRole, id);
            sensorList->addItem(item);
        } else if (sensorType == "Nuvolosita") {
            sensor = std::make_shared<Wind>(id, reliability, name, max, min);
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/Images/cloudiness.png"), sensor->getName());
            item->setData(Qt::UserRole, id);
            sensorList->addItem(item);
        }

        if (sensor) {
            sensorManager.addSensor(sensor);
            qDebug() << "Sensore aggiunto:" << sensor->getName() << "ID:" << sensor->getId();
        }
    }
}


void MainWindow::editSensor() {
    QListWidgetItem *selectedItem = sensorList->currentItem();
    if (!selectedItem) {
        qDebug() << "Nessun sensore selezionato per la modifica!";
        return;
    }

    int id = selectedItem->data(Qt::UserRole).toInt();
    std::shared_ptr<Sensor> sensor = sensorManager.getSensorById(id);

    if (!sensor) {
        qDebug() << "Sensore non trovato per l'ID:" << id;
        return;
    }

    SensorInputDialog dialog(this);
    dialog.setId(sensor->getId());
    dialog.setName(sensor->getName());
    dialog.setReliability(sensor->getReliability());
    dialog.setMax(sensor->getMax());
    dialog.setMin(sensor->getMin());
    dialog.setType(sensor->getType());
    dialog.disableTypeSelection();
    //dialog.disableIdSelection();

    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        double reliability = dialog.getReliability();
        double max = dialog.getMax();
        double min = dialog.getMin();

        sensor->setName(name);
        sensor->setReliability(reliability);
        sensor->setMax(max);
        sensor->setMin(min);

        if (max <= min) {
            QMessageBox::warning(this, "Errore", "Il valore massimo deve essere maggiore del valore minimo.");
            return;
        }

        sensorManager.updateSensor(sensor);
        selectedItem->setText(sensor->getName());

        showSensorInfo();

        qDebug() << "Sensore modificato:" << sensor->getName() << "ID:" << sensor->getId();
    } else {
        qDebug() << "Modifica sensore annullata o non valida.";
    }
}


void MainWindow::deleteSensor() {
    QListWidgetItem *selectedItem = sensorList->currentItem();
    if (!selectedItem) return;

    QString selectedName = selectedItem->text();
    int id = selectedName.toInt();

    // Conferma eliminazione
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Conferma eliminazione",
                                  "Sei sicuro di voler eliminare il sensore?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        sensorManager.removeSensor(id);
        delete selectedItem;
    }
}


void MainWindow::simulateSensor()
{
    QListWidgetItem *selectedItem = sensorList->currentItem();
    if (!selectedItem) return;

    int id = selectedItem->data(Qt::UserRole).toInt();
    qDebug() << "ID selezionato:" << id;

    bool ok;
    int numMeasurements = QInputDialog::getInt(this, tr("Simula Sensore"),
                                               tr("Inserire numero di misurazioni:"),
                                               1, 2, 200, 1, &ok);
    if (ok && numMeasurements > 1) {
        std::shared_ptr<Sensor> sensor = sensorManager.getSensorById(id);
        if (sensor) {
            SimulationVisitor visitor(numMeasurements);

            // Accettare il visitor dal sensore selezionato
            sensor->accept(visitor);

        } else {
            qDebug() << "Sensore non trovato!";
        }
    } else {
        qDebug() << "Input non valido o operazione annullata.";
    }
}


void MainWindow::showSensorInfo() {
    QListWidgetItem *selectedItem = sensorList->currentItem();
    if (!selectedItem) {
        sensorInfoLabel->setText("");
        return;
    }

    int id = selectedItem->data(Qt::UserRole).toInt();
    std::shared_ptr<Sensor> sensor = sensorManager.getSensorById(id);
    if (!sensor) {
        sensorInfoLabel->setText("");
        return;
    }

    QString sensorInfo = "<h3>" + sensor->getName() + " " + "</h3>";
    sensorInfo += "<span><b>Type:</b> " + sensor->getType() + " " + "</span>";
    sensorInfo += "<span><b>ID:</b> " + QString::number(sensor->getId()) + " " + "</span>";
    sensorInfo += "<span><b>Reliability:</b> " + QString::number(sensor->getReliability()) + "% " + "</span>";
    sensorInfo += "<span><b>Max Value:</b> " + QString::number(sensor->getMax()) + " " + "</span>";
    sensorInfo += "<span><b>Min Value:</b> " + QString::number(sensor->getMin()) + " " + "</span>";

    if (auto polvereSensor = std::dynamic_pointer_cast<Dust>(sensor)) {
        sensorInfo += "<span><b>Dust Level:</b> " + polvereSensor->getDustLevelDescription() + " " + "</span>";
    } else if (auto humiditySensor = std::dynamic_pointer_cast<Humidity>(sensor)) {
        double dewPoint = humiditySensor->calculateDewPoint();
        sensorInfo += "<span><b>Dew Point:</b> " + QString::number(dewPoint, 'f', 2) + " °C</span>";
    } else if (auto windSensor = std::dynamic_pointer_cast<Wind>(sensor)) {
        double avgSpeed = windSensor->calculateWindChill();
        sensorInfo += "<span><b>Chill Speed:</b> " + QString::number(avgSpeed, 'f', 2) + " m/s</span>";
    }

    sensorInfoLabel->setText(sensorInfo);
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, "Carica dati", "", "File di testo (*.txt)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            QString sensorType, name;
            int id = 0;
            double reliability = 0.0, max = 0.0, min = 0.0;

            while (!in.atEnd()) {
                QString line = in.readLine();
                QStringList parts = line.split(": ");
                if (parts.length() == 2) {
                    QString key = parts[0];
                    QString value = parts[1];

                    if (key == "Sensor ID")
                        id = value.toInt();
                    else if (key == "Sensor Type")
                        sensorType = value;
                    else if (key == "Sensor Name")
                        name = value;
                    else if (key == "Reliability")
                        reliability = value.toDouble();
                    else if (key == "Max Value")
                        max = value.toDouble();
                    else if (key == "Min Value")
                        min = value.toDouble();
                }

                if (line.isEmpty() || in.atEnd()) {
                    std::shared_ptr<Sensor> sensor;

                    if (sensorType == "Polvere" || sensorType == "dust") {
                        sensor = std::make_shared<Dust>(id, reliability, name, max, min);
                    } else if (sensorType == "Temperatura" || sensorType == "temperature") {
                        sensor = std::make_shared<Temperature>(id, reliability, name, max, min);
                    } else if (sensorType == "Umidita" || sensorType == "humidity") {
                        sensor = std::make_shared<Humidity>(id, reliability, name, max, min);
                    } else if (sensorType == "Vento" || sensorType == "wind") {
                        sensor = std::make_shared<Wind>(id, reliability, name, max, min);
                    } else if (sensorType == "Nuvolosita" || sensorType == "cloudiness") {
                        sensor = std::make_shared<Cloudiness>(id, reliability, name, max, min);
                    }

                    if (sensor) {
                        sensorManager.addSensor(sensor);
                        QString sensorTypeLower = sensorType.toLower();
                        if (sensorTypeLower == "polvere") {
                            sensorTypeLower = "dust";
                        } else if (sensorTypeLower == "temperatura") {
                            sensorTypeLower = "temperature";
                        } else if (sensorTypeLower == "umidita") {
                            sensorTypeLower = "humidity";
                        }
                        QListWidgetItem *item = new QListWidgetItem(QIcon(":/Images/" + sensorTypeLower + ".png"), sensor->getName());
                        item->setData(Qt::UserRole, id);
                        sensorList->addItem(item);
                        qDebug() << "Sensore aggiunto:" << sensor->getName() << "ID:" << sensor->getId();
                    }

                    sensorType.clear();
                    name.clear();
                    id = 0;
                    reliability = 0.0;
                    max = 0.0;
                    min = 0.0;
                }
            }

            file.close();
            sensorList->repaint();
            qDebug() << "Dati caricati con successo!";
        } else {
            qDebug() << "Impossibile aprire il file per la lettura!";
        }
    } else {
        qDebug() << "Nessun file selezionato!";
    }
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this, "Salva dati", "", "File di testo (*.txt)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            for (const auto& sensor : sensorManager.getSensors()) {
                out << "Sensor ID: " << sensor->getId() << "\n";
                out << "Sensor Type: " << sensor->getType() << "\n";
                out << "Sensor Name: " << sensor->getName() << "\n";
                out << "Reliability: " << sensor->getReliability() << "\n";
                out << "Max Value: " << sensor->getMax() << "\n";
                out << "Min Value: " << sensor->getMin() << "\n";
                out << "\n";
            }

            file.close();
            qDebug() << "Dati salvati con successo!";
        } else {
            qDebug() << "Impossibile aprire il file per la scrittura!";
        }
    }
}

void MainWindow::exit() {
    int button = QMessageBox::question(
        this, tr("ClimateHub - Exit"),
        tr("Vuoi davvero uscire?"),
        QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::Yes) {
        close();
    }
}

MainWindow::~MainWindow() {}
