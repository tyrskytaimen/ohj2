#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    cout << "Input file: ";
    std::string input_file_name = "";
    getline(std::cin, input_file_name);

    cout << "Output file: ";
    std::string output_file_name = "";
    getline(std::cin, output_file_name);

    ifstream input_file(input_file_name);
    if(not input_file)
    {
        std::cout << "Error! The file " << input_file_name
                  << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    ofstream output_file(output_file_name);
    std::string line = "";
    int line_number = 1;
    while(getline(input_file, line))
    {
        output_file << line_number << " " << line << std::endl;
        ++line_number;
    }
    input_file.close();
    output_file.close();

    return 0;
}
