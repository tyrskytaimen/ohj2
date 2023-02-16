#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    cout << "Input file: ";
    std::string filename = "";
    getline(std::cin, filename);

    ifstream file(filename);
    if(not file)
    {
        std::cout << "Error! The file " << filename
                  << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    map<std::string, int> scores;
    std::string line = "";
    std::string name = "";
    std::string points = "";
    while(getline(file, name, ':'))
    {
        getline(file, points);
        if(scores.find(name) == scores.end())
        {
            scores.insert({name, stoi(points)});
        }
        else
        {
            scores.at(name) += stoi(points);
        }
    }
    file.close();

    std::cout << "Final scores:" << std::endl;
    for(auto guy : scores)
    {
        std::cout << guy.first << ": " << guy.second << std::endl;
    }
    return EXIT_SUCCESS;
}
