#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool check_key(string text);
bool is_abc(string text);
void encrypt(string text, string key);

int main()
{
    string key = " ";
    cout << "Enter the encryption key: ";
    cin >> key;

    if (check_key(key) == false) {
        return EXIT_FAILURE;
    }

    string msg = " ";
    cout << "Enter the text to be encrypted: ";
    cin >> msg;

    if (is_abc(msg) == false) {
        return EXIT_FAILURE;
    }

    encrypt(msg, key);

    return 0;
}

bool check_key(string text) {
    // Pituus ja aakkoset
    if (text.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    } else if(is_abc(text) == false) {
        return false;
    } else {
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (text.find(ch) == string::npos) {
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return false;
            }
        }
    }
    return true;
}

bool is_abc(string text) {
    string::size_type pituus = text.length();
    for (int i = 0; i < int(pituus); ++i) {
        char x = text.at(i);
        if (islower(x) == false) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }
    }
    return true;
}

void encrypt(string msg, string key) {
    char ch = ' ';
    string new_ch = " ";
    int ascii = 0;
    string::size_type pituus = msg.length();
    for (int i = 0; i < int(pituus); ++i) {
        ch = msg.at(i);
        ascii = static_cast< int >(ch);
        new_ch = key.at(ascii - 97);

        msg.replace(i, 1, new_ch);

    }
    cout << "Encrypted text: " << msg << endl;
}
