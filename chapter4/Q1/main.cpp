#include <iostream>

int main()
{
    std::cout << "Enter your full name: ";
    std::string fullName{};
    std::getline(std::cin >> std::ws, fullName);

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    std::cout << "Your age + length of name is: " << age + static_cast<int>(fullName.length()) << '\n';

    return 0;
}