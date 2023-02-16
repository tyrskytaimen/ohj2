#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a positive number: ";
    cin >> number;

    if (number <= 0) {
        cout << "Only positive numbers accepted" << endl;
    } else {
        int num1 = 0;
        int num2 = 0;
        int diff1 = number;
        int diff2 = 0;

        for (int i = 1; i < number; ++i) {
            // Lasketaan kertoimien välinen etäisyys
            if (i - (number / i) < 0) {
                diff2 = -(i - (number / i));
            } else {
                diff2 = (i - (number / i));
            }
            // Otetaan kertoimet talteen, jos niiden etäisyys on pienempi kuin aiempien
            if (number % i == 0 and diff2 < diff1) {
                diff1 = diff2;
                if (i < number / i) {
                    num1 = i;
                    num2 = number / i;
                } else {
                    num2 = i;
                    num1 = number / i;
                }
            }
        }

        cout << number << " = " << num1 << " * " << num2 << endl;
    }

    return 0;
}
