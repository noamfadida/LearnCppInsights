#include <iostream>

double getDouble();
char getOperator();
void calculateExpression(double, double, char);

double getDouble()
{
    std::cout << "Enter a double value: ";
    double num{};
    std::cin >> num;
    return num;
}

char getOperator()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char op{};
    std::cin >> op;
    return op;
}

void calculateExpression(double num1, double num2, char op)
{
    double result{};
    if (op == '+')
        result = num1 + num2;
    else if (op == '-')
        result = num1 - num2;
    else if (op == '*')
        result = num1 * num2;
    else if (op == '/' && num2 != 0)
        result = num1 / num2;
    else
    {
        std::cout << "Invalid input, please try again\n";
        return;
    }
    std::cout << num1 << ' ' << op << ' ' << num2 << " is " << result << '\n';
}

int main()
{
    double num1{getDouble()};
    double num2{getDouble()};
    char op{getOperator()};
    calculateExpression(num1, num2, op);

    return 0;
}