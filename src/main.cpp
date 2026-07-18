#include <iostream>
#include "calculator.h"

int main() {

    Calculator calc;

    std::cout << "Addition : "
              << calc.add(5,3)
              << std::endl;

    std::cout << "Subtraction : "
              << calc.subtract(10,4)
              << std::endl;

    std::cout << "Multiplication : "
              << calc.multiply(5,5)
              << std::endl;

    std::cout << "Division : "
              << calc.divide(20,4)
              << std::endl;

    return 0;
}