#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i <= 9; ++i) {
        QString buttonName = QString("btn%1").arg(i);
        QPushButton *button = findChild<QPushButton *>(buttonName);
        if (button) {
            connect(button, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
        }
    }

    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(ui->btnSub, &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(ui->btnMul, &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::onOperationClicked);
    connect(ui->btnPow, &QPushButton::clicked, this, &MainWindow::onOperationClicked);

    connect(ui->btnEquals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnSign, &QPushButton::clicked, this, &MainWindow::onSignClicked);
    connect(ui->btnDot, &QPushButton::clicked, this, &MainWindow::onDotClicked);
    connect(ui->btnBackspace, &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);

    connect(ui->btnMC, &QPushButton::clicked, this, &MainWindow::onMemoryClearClicked);
    connect(ui->btnMR, &QPushButton::clicked, this, &MainWindow::onMemoryRecallClicked);
    connect(ui->btnMS, &QPushButton::clicked, this, &MainWindow::onMemorySaveClicked);

    SetText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString &text) {
    QString normalized = NormalizeNumber(text);
    input_number_ = normalized;
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::AddText(const QString &suffix) {
    if (current_operation_ != Operation::NO_OPERATION && input_number_.isEmpty()) {
        input_number_ = "0";
    }
    SetText(input_number_ + suffix);
}

void MainWindow::onDigitClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        AddText(button->text());
    }
}

void MainWindow::onOperationClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    Operation op = Operation::NO_OPERATION;
    if (button == ui->btnAdd) op = Operation::ADDITION;
    else if (button == ui->btnSub) op = Operation::SUBTRACTION;
    else if (button == ui->btnMul) op = Operation::MULTIPLICATION;
    else if (button == ui->btnDiv) op = Operation::DIVISION;
    else if (button == ui->btnPow) op = Operation::POWER;

    SetOperation(op);
}

void MainWindow::SetOperation(Operation op) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    } else {
    }

    current_operation_ = op;
    ui->l_formula->setText(QString("%1 %2").arg(calculator_.GetNumber()).arg(OpToString(op)));
    input_number_.clear();
}

QString MainWindow::OpToString(Operation op) {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::SUBTRACTION: return "−";
    case Operation::MULTIPLICATION: return "×";
    case Operation::DIVISION: return "÷";
    case Operation::POWER: return "^";
    }
    return "";
}

void MainWindow::onEqualsClicked() {
    if (current_operation_ == Operation::NO_OPERATION) return;

    QString formula = QString("%1 %2 %3 =").arg(calculator_.GetNumber())
                          .arg(OpToString(current_operation_))
                          .arg(active_number_);
    ui->l_formula->setText(formula);

    switch(current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(active_number_);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case Operation::DIVISION:
        calculator_.Div(active_number_);
        break;
    case Operation::POWER:
        calculator_.Pow(active_number_);
        break;
    case Operation::NO_OPERATION:
        break;
    }

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_.clear();
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::onClearClicked() {
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("0");
}

void MainWindow::onSignClicked() {
    if (input_number_.startsWith("-")) {
        SetText(input_number_.mid(1));
    } else {
        SetText("-" + input_number_);
    }
}

void MainWindow::onDotClicked() {
    if (!input_number_.contains('.')) {
        AddText(".");
    }
}

void MainWindow::onBackspaceClicked() {
    if (input_number_.isEmpty() || input_number_ == "0") {
        return;
    }

    input_number_.chop(1);
    if (input_number_.isEmpty() || input_number_ == "-") {
        SetText("0");
    } else {
        SetText(input_number_);
    }
}

void MainWindow::onMemoryClearClicked() {
    memory_set_ = false;
    ui->l_memory->setText("");
}

void MainWindow::onMemoryRecallClicked() {
    if (memory_set_) {
        active_number_ = memory_;
        ui->l_result->setText(QString::number(active_number_));
        input_number_.clear();
    }
}

void MainWindow::onMemorySaveClicked() {
    memory_ = active_number_;
    memory_set_ = true;
    ui->l_memory->setText("M");
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-') && text.length() > 1) {
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && text != "0" && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "0";
}
