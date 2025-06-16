#include "calculator.h"
#include <cmath>

void Calculator::Set(double value) {
    current_value_ = value;
}

double Calculator::GetNumber() const {
    return current_value_;
}

void Calculator::Add(double value) {
    current_value_ += value;
}

void Calculator::Sub(double value) {
    current_value_ -= value;
}

void Calculator::Mul(double value) {
    current_value_ *= value;
}

void Calculator::Div(double value) {
    if (value != 0) {
        current_value_ /= value;
    } else {
        current_value_ = NAN; // Not a Number
    }
}

void Calculator::Pow(double value) {
    current_value_ = std::pow(current_value_, value);
}
