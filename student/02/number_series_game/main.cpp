#include <iostream>


int main()
{
    int amount = 0;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> amount;

    for (int i = 1; i < amount + 1; ++i) {
        if (i % 3 == 0 and i % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        } else if (i % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else if (i % 7 == 0) {
            std::cout << "boing" << std::endl;
        } else {
        std::cout << i << std::endl;
        }
    }
}
