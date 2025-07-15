#pragma once

#include <string>
#include <sstream>
#include "calculator.h"
#include "mainwindow.h"
#include "rational.h"

template<class T>
std::string ToString(T number) {
    std::ostringstream tmp_str;
    tmp_str << number;
    return tmp_str.str();
}

template<>
std::string ToString<Rational>(Rational number) {
    std::ostringstream tmp_str;
    if (number.GetDenominator() == 1) {
        tmp_str << number.GetNumerator();
    } else {
        tmp_str << number.GetNumerator() << " / " << number.GetDenominator();
    }
    return tmp_str.str();
}

template<class T>
T FromString(const std::string& number) {
    std::istringstream tmp_str{number};
    T result{};
    tmp_str >> result;
    return result;
}

template<>
Rational FromString<Rational>(const std::string& number) {
    std::istringstream tmp_str{number};
    int numerator = 0;
    int denominator = 1;
    char slash = 0;

    tmp_str >> numerator;
    if (tmp_str.peek() == '/') {
        tmp_str >> slash >> denominator;
    }

    return Rational(numerator, denominator);
}

inline std::string ToString(std::uint8_t number) {
    std::ostringstream tmp_str;
    tmp_str << +number;
    return tmp_str.str();
}

template<>
std::uint8_t FromString<std::uint8_t>(const std::string& number) {
    std::istringstream tmp_str{number};
    unsigned result{};
    tmp_str >> result;
    return static_cast<std::uint8_t>(result);
}

template<class Number>
class Controller
{
public:
    Controller() {}

    void BindWithMainWindow(MainWindow* main_window) {
        view_ = main_window;
        if (!view_) {
            return;
        }

        view_->SetDigitKeyCallback([this](int key){
            PressDigitKey(key);
        });
        view_->SetProcessOperationKeyCallback([this](Operation key){
            ProcessOperationKey(key);
        });
        view_->SetProcessControlKeyCallback([this](ControlKey key){
            ProcessControlKey(key);
        });

        RevealView();
    }

private:
    void PressDigitKey(int digit) {
        AddChar(digit + '0');
    }

    void ProcessOperationKey(Operation operation) {
        switch(operation) {
        case Operation::ADDITION:
            OnOperation([this](Number x){return calculator_.Add(x);}, " + ");
            break;
        case Operation::SUBTRACTION:
            OnOperation([this](Number x){return calculator_.Sub(x);}, " − ");
            break;
        case Operation::MULTIPLICATION:
            OnOperation([this](Number x){return calculator_.Mul(x);}, " × ");
            break;
        case Operation::DIVISION:
            OnOperation([this](Number x){return calculator_.Div(x);}, " ÷ ");
            break;
        case Operation::POWER:
            OnOperation([this](Number x){return calculator_.Pow(x);}, " ^ ");
            break;
        }
    }

    void ProcessControlKey(ControlKey key) {
        switch(key) {
        case ControlKey::EQUALS: {
            if (!operation_) {
                return;
            }
            std::ostringstream formula;
            formula << ToString(calculator_.GetNumber()) << operation_name_ << ToString(active_number_) << " = ";
            auto error = operation_(active_number_);
            if (error.has_value()) {
                SetErrorInView(error.value());
                break;
            }
            SetFormulaInView(formula.str());
            SetInputAsNumber(calculator_.GetNumber());
            operation_ = {};
            break;
        }
        case ControlKey::CLEAR:
            SetInputAsNumber(Number{});
            SetFormulaInView("");
            operation_ = {};
            break;
        case ControlKey::MEM_SAVE:
            calculator_.Save();
            SetMemInView("M");
            break;
        case ControlKey::MEM_LOAD:
            calculator_.Load();
            SetInputAsNumber(calculator_.GetNumber());
            break;
        case ControlKey::MEM_CLEAR:
            SetMemInView("");
            break;
        case ControlKey::PLUS_MINUS:
            if (input_as_number_) {
                active_number_ = -active_number_;
                SetInputAsNumber(active_number_);
            } else {
                if (input_.size() && input_.front() == '-') {
                    SetInputAsString(input_.substr(1));
                } else {
                    SetInputAsString("-" + input_);
                }
            }
            break;
        case ControlKey::BACKSPACE:
            if (input_.size() > 0) {
                SetInputAsString(input_.substr(0, input_.size() - 1));
            }
            break;
        case ControlKey::EXTRA_KEY:
            DoExtraAction();
            break;
        }
    }

    std::optional<std::string> GetExtraKey() const {
        if constexpr (std::is_integral_v<Number>) {
            return std::nullopt;
        }
        if constexpr (std::is_same_v<Number, Rational>) {
            return "/";
        }
        return ".";
    }

    void OnOperation(std::function<std::optional<Error> (Number)> action, std::string text) {
        if (!operation_) {
            calculator_.Set(active_number_);
        }

        operation_name_ = text;
        operation_ = action;
        input_ = "";

        std::ostringstream oss;
        oss << ToString(calculator_.GetNumber()) << text;
        SetFormulaInView(oss.str());
    }

    void SetInputAsString(const std::string& new_input) {
        input_as_number_ = false;
        input_ = new_input;

        try {
            active_number_ = FromString<Number>(input_);
            if constexpr (std::is_same_v<Number, Rational>) {
                UpdateInputInView(ToString(active_number_));
            } else {
                UpdateInputInView(input_);
            }
        } catch (...) {
            UpdateInputInView(input_);
        }
    }

    void SetInputAsNumber(Number number) {
        input_as_number_ = true;
        input_ = "";
        active_number_ = number;
        UpdateInputInView(ToString(active_number_));
    }

    void AddChar(char character) {
        SetInputAsString(input_ + character);
    }

    void DoExtraAction() {
        if constexpr (std::is_integral_v<Number>) {
            return;
        }
        if constexpr (std::is_same_v<Number, Rational>) {
            if (input_.size() == 0 || input_.find('/') != std::string::npos) {
                return;
            }
            AddChar('/');
        } else {
            if (input_.find('.') != std::string::npos) {
                return;
            }
            AddChar('.');
        }
    }

    void UpdateInputInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetInputText(string);
        text_ = string;
    }

    void SetErrorInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetErrorText(string);
    }

    void SetFormulaInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetFormulaText(string);
        formula_ = string;
    }

    void SetMemInView(const std::string& string) {
        if (!view_) {
            return;
        }
        view_->SetMemText(string);
        mem_text_ = string;
    }

    void RevealView() {
        if (!view_) {
            return;
        }
        view_->SetInputText(text_);
        view_->SetFormulaText(formula_);
        view_->SetMemText(mem_text_);
        view_->SetExtraKey(GetExtraKey());
    }

private:
    std::function<std::optional<Error>(Number number)> operation_;
    std::string operation_name_;

    Calculator<Number> calculator_;

    Number active_number_ = {};
    std::string input_;

    MainWindow* view_ = nullptr;

    bool input_as_number_ = true;

    std::string text_;
    std::string formula_;
    std::string mem_text_;
};
