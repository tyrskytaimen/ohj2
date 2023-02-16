#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


void print(const std::map<std::string,std::vector<std::string>>& vec, std::string name, int n = 1)
{
    std::cout << name << std::endl;
    if (vec.find(name) == vec.end() || vec.at(name).size() == 0)
    {
        return;
    }
    else
    {
        for (auto id : vec.at(name))
        {
            for (int i = 0; i < n; i++)
            {
                std::cout << "..";
            }
            print(vec, id, n+1);
        }
    }
}

void count(const std::map<std::string,std::vector<std::string>>& vec, std::string name, int& n)
{
    if (vec.find(name) == vec.end() || vec.at(name).size() == 0)
    {
        return;
    }
    else
    {
        for (auto id : vec.at(name))
        {
            ++n;
            count(vec, id, n);
        }
    }
}

void depth(const std::map<std::string,std::vector<std::string>>& vec, std::string name, int n, int& p)
{
    ++n;
    if (vec.find(name) == vec.end() || vec.at(name).size() == 0)
    {
        if (n > p)
        {
            p = n;
        }
        return;
    }
    else
    {
        for (auto id : vec.at(name))
        {
            depth(vec, id, n, p);
        }
    }
}

int main()
{
    std::map<std::string,std::vector<std::string>> networks;


    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            networks.insert({id1, std::vector<std::string> ()});
            networks.at(id1).push_back(id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(networks, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int rounds = 0;
            count(networks, id, rounds);
            std::cout << rounds << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int i = 0;
            int longest = 0;
            depth(networks, id, i, longest);
            std::cout << longest << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
