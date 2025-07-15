#pragma once

#include <iostream>
#include <numeric>
#include <stdexcept>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}
    Rational(int numerator, int denominator = 1) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        int gcd = std::gcd(numerator, denominator);
        numerator_ = numerator / gcd;
        denominator_ = denominator / gcd;

        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    Rational& operator+=(const Rational& other) {
        int lcm = std::lcm(denominator_, other.denominator_);
        numerator_ = numerator_ * (lcm / denominator_) + other.numerator_ * (lcm / other.denominator_);
        denominator_ = lcm;
        *this = Rational(numerator_, denominator_);
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        return *this += -other;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        *this = Rational(numerator_, denominator_);
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        if (other.numerator_ == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return *this *= Rational(other.denominator_, other.numerator_);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        if (r.denominator_ == 1) {
            os << r.numerator_;
        } else {
            os << r.numerator_ << " / " << r.denominator_;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r) {
        int num, denom = 1;
        char slash = 0;

        is >> num;
        if (is.peek() == '/') {
            is >> slash >> denom;
        }

        r = Rational(num, denom);
        return is;
    }

    friend bool operator==(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator_ == rhs.numerator_ && lhs.denominator_ == rhs.denominator_;
    }

    friend bool operator!=(const Rational& lhs, const Rational& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator_ * rhs.denominator_ < rhs.numerator_ * lhs.denominator_;
    }

    friend bool operator>(const Rational& lhs, const Rational& rhs) {
        return rhs < lhs;
    }

    friend bool operator<=(const Rational& lhs, const Rational& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>=(const Rational& lhs, const Rational& rhs) {
        return !(lhs < rhs);
    }

private:
    int numerator_;
    int denominator_;
};

inline Rational operator+(Rational lhs, const Rational& rhs) {
    lhs += rhs;
    return lhs;
}

inline Rational operator-(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Rational operator*(Rational lhs, const Rational& rhs) {
    lhs *= rhs;
    return lhs;
}

inline Rational operator/(Rational lhs, const Rational& rhs) {
    lhs /= rhs;
    return lhs;
}
