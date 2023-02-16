#include <iostream>

double getHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    double height{};
    std::cin >> height;
    return height;
}

double calculateExponent(double base, int exponent)
{
    double result{1};
    while (exponent--)
    {
        result *= base;
    }
    return result;
}

double calculateHeight(double towerHeight, double seconds)
{
    constexpr double gravity = 9.8; // gravity constant m/s^2
    const double currHeight{towerHeight - gravity * calculateExponent(seconds, 2) / 2};
    return currHeight;
}

void calculatePrintHeight(double towerHeight, double seconds)
{
    double currHeight{calculateHeight(towerHeight, seconds)};
    if (currHeight <= 0.0)
        std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
    else
        std::cout << "At " << seconds << " seconds, the ball is at height: " << currHeight << " meters\n";
}
int main()
{
    constexpr int maxSeconds = 5; // Max seconds to print the calculated height of the ball;
    const double towerHeight{getHeight()};
    for (int t = 0; t <= maxSeconds; t++)
    {
        calculatePrintHeight(towerHeight, t);
    }
    return 0;
}