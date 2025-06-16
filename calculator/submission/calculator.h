#pragma once

class Calculator {
public:
    void Set(double value);
    double GetNumber() const;

    void Add(double value);
    void Sub(double value);
    void Mul(double value);
    void Div(double value);
    void Pow(double value);

private:
    double current_value_ = 0;
};
