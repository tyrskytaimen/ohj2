#include <iostream>

using namespace std;

unsigned long int factorial(int num);
bool check_input(int total, int drawn);

int main()
{
    int total = 0;
    int drawn = 0;

    cout << "Enter the total number of lottery balls: ";
    cin >> total;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

    if (check_input(total, drawn)) {
        int probability = factorial(total) / (factorial(total - drawn) * factorial(drawn));
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << probability << endl;
    }

    return 0;
}

unsigned long int factorial(int num) {
    unsigned long int x = 1;

    for (int i = 1; i <= num; ++i) {
        x = x * i;
    }
    return x;
}

bool check_input(int total, int drawn) {
    if (drawn < 0 or total < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return false;
    } else if (total < drawn) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return false;
    } else {
        return true;
    }
}
