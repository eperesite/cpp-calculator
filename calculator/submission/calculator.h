#pragma once

using Number = double;

class Calculator {
public:
    void Set(Number value);
    Number GetNumber() const;

    void Add(Number value);
    void Sub(Number value);
    void Mul(Number value);
    void Div(Number value);
    void Pow(Number value);

private:
    Number current_value_ = 0;
};
