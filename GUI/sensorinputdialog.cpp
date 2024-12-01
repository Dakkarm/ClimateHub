#include "sensorinputdialog.h"
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QIcon>

SensorInputDialog::SensorInputDialog(QWidget *parent) : QDialog(parent) {

    setMinimumSize(400, 300);
    resize(400, 300);

    createLayout();
    applyStyle();
}

void SensorInputDialog::createLayout() {
    typeComboBox = new QComboBox(this);
    typeComboBox->addItems({"Polvere", "Temperatura", "Umidita", "Vento"});
    typeComboBox->setToolTip("Seleziona il tipo di sensore");

    idSpinBox = new QSpinBox(this);
    idSpinBox->setRange(0, 10000);
    idSpinBox->setToolTip("Inserisci l'ID del sensore");

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText("Nome del sensore");
    nameLineEdit->setToolTip("Inserisci il nome del sensore");

    reliabilitySpinBox = new QDoubleSpinBox(this);
    reliabilitySpinBox->setRange(0, 100);
    reliabilitySpinBox->setSuffix(" %");
    reliabilitySpinBox->setToolTip("Inserisci l'affidabilità del sensore (0-100%)");

    maxSpinBox = new QDoubleSpinBox(this);
    maxSpinBox->setRange(-1000, 1000);
    maxSpinBox->setToolTip("Inserisci il valore massimo misurabile");

    minSpinBox = new QDoubleSpinBox(this);
    minSpinBox->setRange(-1000, 1000);
    minSpinBox->setToolTip("Inserisci il valore minimo misurabile");

    QGroupBox *sensorInfoGroup = new QGroupBox("Informazioni del Sensore", this);
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(new QLabel("Tipo"), 0, 0);
    gridLayout->addWidget(typeComboBox, 0, 1);
    gridLayout->addWidget(new QLabel("ID"), 1, 0);
    gridLayout->addWidget(idSpinBox, 1, 1);
    gridLayout->addWidget(new QLabel("Nome"), 2, 0);
    gridLayout->addWidget(nameLineEdit, 2, 1);
    gridLayout->addWidget(new QLabel("Affidabilità"), 3, 0);
    gridLayout->addWidget(reliabilitySpinBox, 3, 1);
    gridLayout->addWidget(new QLabel("Valore massimo"), 4, 0);
    gridLayout->addWidget(maxSpinBox, 4, 1);
    gridLayout->addWidget(new QLabel("Valore minimo"), 5, 0);
    gridLayout->addWidget(minSpinBox, 5, 1);
    sensorInfoGroup->setLayout(gridLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    buttonBox->button(QDialogButtonBox::Ok)->setObjectName("okButton");
    buttonBox->button(QDialogButtonBox::Cancel)->setObjectName("cancelButton");

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(sensorInfoGroup);
    mainLayout->addWidget(buttonBox);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(20);

    setLayout(mainLayout);
}

void SensorInputDialog::applyStyle() {
    setStyleSheet(
        "QDialog {"
        "}"

        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 1px solid gray;"
        "    border-radius: 5px;"
        "    margin-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    subcontrol-position: top center;"
        "    padding: 0 3px;"
        "}"
        "QLabel {"
        "    font-size: 16px;"
        "    color: #333;"
        "}"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "    font-size: 16px;"
        "    color: #6c757d;"
        "}"
        "QPushButton {"
        "    font-size: 16px;"
        "    padding: 12px 24px;"
        "    border-radius: 5px;"
        "    color: white;"
        "    border: none;"
        "    outline: none;"
        "}"
        "QPushButton#okButton {"
        "    background-color: #4caf50;"
        "}"
        "QPushButton#okButton:hover {"
        "    background-color: #388e3c;"
        "}"
        "QPushButton#okButton:pressed {"
        "    background-color: #2e7d32;"
        "}"
        "QPushButton#cancelButton {"
        "    background-color: #f44336;"
        "}"
        "QPushButton#cancelButton:hover {"
        "    background-color: #e53935;"
        "}"
        "QPushButton#cancelButton:pressed {"
        "    background-color: #d32f2f;"
        "}"
        );
}

QString SensorInputDialog::getType() const {
    return typeComboBox->currentText();
}

int SensorInputDialog::getId() const {
    return idSpinBox->value();
}

QString SensorInputDialog::getName() const {
    return nameLineEdit->text();
}

double SensorInputDialog::getReliability() const {
    return reliabilitySpinBox->value();
}

double SensorInputDialog::getMax() const {
    return maxSpinBox->value();
}

double SensorInputDialog::getMin() const {
    return minSpinBox->value();
}

void SensorInputDialog::setType(const QString &type) {
    int index = typeComboBox->findText(type);
    if (index != -1) {
        typeComboBox->setCurrentIndex(index);
    }
}

void SensorInputDialog::setId(int id) {
    idSpinBox->setValue(id);
}

void SensorInputDialog::setName(const QString &name) {
    nameLineEdit->setText(name);
}

void SensorInputDialog::setReliability(double reliability) {
    reliabilitySpinBox->setValue(reliability);
}

void SensorInputDialog::setMax(double max) {
    maxSpinBox->setValue(max);
}

void SensorInputDialog::setMin(double min) {
    minSpinBox->setValue(min);
}

void SensorInputDialog::disableTypeSelection() {
    typeComboBox->setDisabled(true);
}

//void SensorInputDialog::disableIdSelection() {
//  idSpinBox->setDisabled(true);
//}
