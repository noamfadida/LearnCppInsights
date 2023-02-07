#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int number{};
    std::cin >> number;

    std::cout << "Double " << number << " is: " << 2 * number << '\n';
    std::cout << "Triple " << number << " is: " << 3 * number << '\n';
}