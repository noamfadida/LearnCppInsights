#include <iostream>

int readNumber()
{
    std::cout << "Enter a number: ";
    int input{};
    std::cin >> input;
    return input;
}

void writeAnswer(int num)
{
    std::cout << "The sum is: " << num << '\n';
}

int main()
{
    int a{readNumber()};
    int b{readNumber()};
    writeAnswer(a + b);
    return 0;
}