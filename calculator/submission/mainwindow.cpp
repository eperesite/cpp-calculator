#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect digit buttons
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = QString("btn%1").arg(i);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
        }
    }

    // Connect operation buttons
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::onOperationButtonClicked);
    connect(ui->btnSub, &QPushButton::clicked, this, &MainWindow::onOperationButtonClicked);
    connect(ui->btnMul, &QPushButton::clicked, this, &MainWindow::onOperationButtonClicked);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::onOperationButtonClicked);
    connect(ui->btnPow, &QPushButton::clicked, this, &MainWindow::onOperationButtonClicked);

    // Connect control buttons
    connect(ui->btnEquals, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->btnMS, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->btnMR, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->btnMC, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->btnSign, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->btnBackspace, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);
    connect(ui->tb_extra, &QPushButton::clicked, this, &MainWindow::onControlButtonClicked);

    // Connect controller type change
    connect(ui->cmb_controller, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onControllerChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key) {
        ui->tb_extra->setText(QString::fromStdString(*key));
        ui->tb_extra->setVisible(true);
    } else {
        ui->tb_extra->setVisible(false);
    }
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_cb_ = cb;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_cb_ = cb;
}

void MainWindow::onDigitButtonClicked() {
    if (!digit_cb_) return;

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int digit = button->text().toInt();
        digit_cb_(digit);
    }
}

void MainWindow::onOperationButtonClicked() {
    if (!operation_cb_) return;

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString op = button->text();
    if (op == "+") {
        operation_cb_(Operation::ADDITION);
    } else if (op == "−") {
        operation_cb_(Operation::SUBTRACTION);
    } else if (op == "×") {
        operation_cb_(Operation::MULTIPLICATION);
    } else if (op == "÷") {
        operation_cb_(Operation::DIVISION);
    } else if (op == "xʸ") {
        operation_cb_(Operation::POWER);
    }
}

void MainWindow::onControlButtonClicked() {
    if (!control_cb_) return;

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString text = button->text();
    if (text == "=") {
        control_cb_(ControlKey::EQUALS);
    } else if (text == "C") {
        control_cb_(ControlKey::CLEAR);
    } else if (text == "MS") {
        control_cb_(ControlKey::MEM_SAVE);
    } else if (text == "MR") {
        control_cb_(ControlKey::MEM_LOAD);
    } else if (text == "MC") {
        control_cb_(ControlKey::MEM_CLEAR);
    } else if (text == "±") {
        control_cb_(ControlKey::PLUS_MINUS);
    } else if (text == "⌫") {
        control_cb_(ControlKey::BACKSPACE);
    } else if (button == ui->tb_extra) {
        control_cb_(ControlKey::EXTRA_KEY);
    }
}

void MainWindow::onControllerChanged() {
    if (!controller_cb_) return;

    QString type = ui->cmb_controller->currentText();
    if (type == "double") {
        controller_cb_(ControllerType::DOUBLE);
    } else if (type == "float") {
        controller_cb_(ControllerType::FLOAT);
    } else if (type == "uint8_t") {
        controller_cb_(ControllerType::UINT8_T);
    } else if (type == "int") {
        controller_cb_(ControllerType::INT);
    } else if (type == "int64_t") {
        controller_cb_(ControllerType::INT64_T);
    } else if (type == "size_t") {
        controller_cb_(ControllerType::SIZE_T);
    } else if (type == "Rational") {
        controller_cb_(ControllerType::RATIONAL);
    }
}
