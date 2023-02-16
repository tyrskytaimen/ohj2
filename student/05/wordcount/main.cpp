#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
    cout << "Input file: ";
    string filename = "";
    getline(cin, filename);

    ifstream file(filename);
    if(not file)
    {
        cout << "Error! The file " << filename
                  << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, pair<int, vector<int>>> words;
    int row = 1;
    string line = "";
    string word = "";
    while(getline(file, line))
    {
        for(unsigned int i = 0; i < line.length(); ++i)
        {
            if(line.at(i) != ' ')
            {
                word += line.at(i);
            }
            else
            {
                if(words.find(word) == words.end())
                {
                    words.insert({word, make_pair(1, vector<int> ())});
                    words.at(word).second.push_back(row);
                }
                else
                {
                    if(find(words.at(word).second.begin(), words.at(word).second.end(), row)
                            == words.at(word).second.end())
                    {
                        words.at(word).first += 1;
                        words.at(word).second.push_back(row);
                    }
                }
                word.clear();
            }
        }
        // Tallennetaan rivin viimeinen sana
        if(words.find(word) == words.end())
        {
            words.insert({word, make_pair(1, vector<int> ())});
            words.at(word).second.push_back(row);
        }
        else
        {
            if(find(words.at(word).second.begin(), words.at(word).second.end(), row)
                    == words.at(word).second.end())
            {
                words.at(word).first += 1;
                words.at(word).second.push_back(row);
            }
        }
        word.clear();
        ++row;
    }
    file.close();
    for(auto i : words)
    {
        // Tulostetaan sanan määrä ja ensimmäinen esiintymisrivi
        cout << i.first + " " << i.second.first
             << ": " << i.second.second.at(0);
        // Tulostetaan loput esiintymisrivit
        for(unsigned int n = 1; n < i.second.second.size(); ++n)
        {
            cout << ", " << i.second.second.at(n);
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}
