#include <gtest/gtest.h>
#include "calculator.h"

TEST(CalculatorTest, Addition)
{
    Calculator calc;
    EXPECT_EQ(calc.add(5,3),8);
}

TEST(CalculatorTest, Subtraction)
{
    Calculator calc;
    EXPECT_EQ(calc.subtract(10,4),6);
}

TEST(CalculatorTest, Multiplication)
{
    Calculator calc;
    EXPECT_EQ(calc.multiply(5,5),25);
}

TEST(CalculatorTest, Division)
{
    Calculator calc;
    EXPECT_DOUBLE_EQ(calc.divide(10,2),5);
}

TEST(CalculatorTest, DivideByZero)
{
    Calculator calc;

    EXPECT_THROW(calc.divide(10,0), std::runtime_error);
}