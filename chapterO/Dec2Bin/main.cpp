#include <iostream>

/*
Write a program that asks the user to input a number between 0 and 255.
Print this number as an 8-bit binary number (of the form #### ####).
Don’t use any bitwise operators. Don’t use std::bitset.
*/

int printAndDecrementBit(int num, int powerOfTwo)
{
    bool isOne{num >= powerOfTwo};
    std::cout << (isOne ? '1' : '0');
    return isOne ? num - powerOfTwo : num;
}

void printBinary(int num)
{
    if (!(num >= 0 && num <= 255))
        std::cout << "Error! Please enter a valid number!\n";
    else
    {
        num = printAndDecrementBit(num, 128);
        num = printAndDecrementBit(num, 64);
        num = printAndDecrementBit(num, 32);
        num = printAndDecrementBit(num, 16);
        std::cout << ' ';
        num = printAndDecrementBit(num, 8);
        num = printAndDecrementBit(num, 4);
        num = printAndDecrementBit(num, 2);
        num = printAndDecrementBit(num, 1);
        std::cout << '\n';
    }
}

int main()
{
    std::cout << "Enter a number between 0 and 255: ";
    int num{};
    std::cin >> num;
    printBinary(num);
    return 0;
}