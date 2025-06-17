#include "calculator.h"
#include <cmath>

void Calculator::Set(Number value) {
    current_value_ = value;
}

Number Calculator::GetNumber() const {
    return current_value_;
}

void Calculator::Add(Number value) {
    current_value_ += value;
}

void Calculator::Sub(Number value) {
    current_value_ -= value;
}

void Calculator::Mul(Number value) {
    current_value_ *= value;
}

void Calculator::Div(Number value) {
    if (value != 0) {
        current_value_ /= value;
    } else {
        current_value_ = NAN;
    }
}

void Calculator::Pow(Number value) {
    current_value_ = std::pow(current_value_, value);
}
