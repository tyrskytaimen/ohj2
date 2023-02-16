#include <iostream>
#include <string>
#include <vector>


std::vector< std::string > split(const std::string& line, char separator, bool spaces = false)
{
    std::vector< std::string > list;
    std::vector< unsigned int > index;
    std::string::size_type length = line.length();

    //Etsitään erotusmerkkien indexit
    std::string::size_type i = -1;
    while (i + 1 < length)
    {
        i = line.find(separator, i + 1);

        if (i == std::string::npos)
        {
            break;
        }
        else
        {
            index.push_back(i);
        }
    }

    std::string::size_type size = index.size();

    if (size == 0)
    {
        list.push_back(line);
        return list;
    }

    int x;
    std::string part;
    if (spaces == false or index.front() != 0)
    {
        part = line.substr(0,index.front());
        list.push_back(part);
    }


    for (unsigned int n = 0; n + 1 < size; ++n)
    {
        x = index.at(n + 1) - index.at(n);

        if (x == 1)
        {
            if (spaces == false)
            {
                list.push_back("");
            }
        }
        else
        {
            part = line.substr(index.at(n) + 1, x - 1);
            list.push_back(part);
        }
    }

    part = line.substr(index.back() + 1);
    list.push_back(part);


    return list;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
