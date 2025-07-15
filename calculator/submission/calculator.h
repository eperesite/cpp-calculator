#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<class Number>
class Calculator {
public:
    Calculator() : number_{}, has_mem_(false), mem_{} {}

    void Set(Number number) {
        number_ = number;
    }

    Number GetNumber() const {
        return number_;
    }

    bool GetHasMem() const {
        return has_mem_;
    }

    void Save() {
        mem_ = number_;
        has_mem_ = true;
    }

    void Load() {
        if (has_mem_) {
            number_ = mem_;
        }
    }

    std::optional<Error> Add(Number x) {
        number_ += x;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number x) {
        number_ -= x;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number x) {
        number_ *= x;
        return std::nullopt;
    }

    std::optional<Error> Div(Number x) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (x == Number{0}) {
                return "Division by zero";
            }
        }
        number_ /= x;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number x) {
        if constexpr (std::is_integral_v<Number>) {
            if (number_ == Number{0} && x == Number{0}) {
                return "Zero power to zero";
            }
            if (x < Number{0}) {
                return "Integer negative power";
            }
            number_ = static_cast<Number>(::Pow(number_, x));
        }
        else if constexpr (std::is_same_v<Number, Rational>) {
            if (number_ == Number{0} && x == Number{0}) {
                return "Zero power to zero";
            }
            if (x.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            number_ = ::Pow(number_, x);
        }
        else {
            number_ = static_cast<Number>(std::pow(number_, x));
        }
        return std::nullopt;
    }

private:
    Number number_;
    bool has_mem_;
    Number mem_;
};
