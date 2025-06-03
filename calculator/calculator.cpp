#include "calculator.h"
#include <string>
#include <sstream>
#include <cmath>

bool ReadNumber(Number& result) {
    std::string token;
    if (!(std::cin >> token)) {
        std::cerr << "Error: Numeric operand expected\n";
        return false;
    }

    std::istringstream iss(token);
    if (!(iss >> result) || !iss.eof()) {
        std::cerr << "Error: Numeric operand expected\n";
        return false;
    }

    return true;
}

bool RunCalculatorCycle() {
    Number current = 0;
    Number memory = 0;
    bool memorySet = false;

    if (!ReadNumber(current)) return false;

    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            Number value;
            if (!ReadNumber(value)) return false;
            current += value;
        } else if (command == "-") {
            Number value;
            if (!ReadNumber(value)) return false;
            current -= value;
        } else if (command == "*") {
            Number value;
            if (!ReadNumber(value)) return false;
            current *= value;
        } else if (command == "/") {
            Number value;
            if (!ReadNumber(value)) return false;
            current /= value;
        } else if (command == "**") {
            Number value;
            if (!ReadNumber(value)) return false;
            current = std::pow(current, value);
        } else if (command == "=") {
            std::cout << current << '\n';
        } else if (command == ":") {
            Number value;
            if (!ReadNumber(value)) return false;
            current = value;
        } else if (command == "c") {
            current = 0;
        } else if (command == "q") {
            return true;
        } else if (command == "s") {
            memory = current;
            memorySet = true;
        } else if (command == "l") {
            if (!memorySet) {
                std::cerr << "Error: Memory is empty\n";
                return false;
            }
            current = memory;
        } else {
            std::cerr << "Error: Unknown token " << command << '\n';
            return false;
        }
    }

    return false;
}
