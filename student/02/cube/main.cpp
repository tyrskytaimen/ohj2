#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a number: ";
    cin >> number;

    if (number == 0) {
        cout << "The cube of " << number << " is " << number << "." << endl;
    } else {
        int result = number * number * number;
        int checksum = (result / number) / number;

        if (checksum != number) {
            cout << "Error! The cube of "<< number << " is not " << result << "." << endl;
        } else {
            cout << "The cube of " << number << " is " << result << "." << endl;
        }
    }

    return 0;
}
