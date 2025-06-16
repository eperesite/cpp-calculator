#pragma once

#include "calculator.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDigitClicked();
    void onOperationClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onSignClicked();
    void onDotClicked();
    void onBackspaceClicked();
    void onMemoryClearClicked();
    void onMemoryRecallClicked();
    void onMemorySaveClicked();

private:
    enum class Operation {
        NO_OPERATION,
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        POWER
    };

    Ui::MainWindow *ui;
    Calculator calculator_;
    QString input_number_;
    double active_number_ = 0;
    Operation current_operation_ = Operation::NO_OPERATION;
    double memory_ = 0;
    bool memory_set_ = false;

    void SetText(const QString &text);
    void AddText(const QString &suffix);
    void SetOperation(Operation op);
    static QString OpToString(Operation op);
    QString NormalizeNumber(const QString &text);
    QString RemoveTrailingZeroes(const QString &text);
};
