#include <iostream>
#include <string>

bool is_num(const char c)
{
    if(c >= 48 and c <= 57) //ASCII-koodit
    {
        return true;
    }
    return false;
}

int main()
{
    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl
              << "EXPR> ";

    int array[80];
    int* pointer = array;
    int nums = 0;
    int oper = 0;
    while(true)
    {
        char c;
        std::cin >> c;

        if(is_num(c))
        {
            *pointer = c - 48;
            ++pointer;
            ++nums;
            continue;
        }

        if(nums == 0)
        {
            std::cout << "Error: Expression must start with a number" << std::endl;
            return EXIT_FAILURE;
        }

        if(c == '+')
        {
            *(pointer - 2) = *(pointer - 2) + *(pointer - 1);
        }
        else if(c == '-')
        {
            *(pointer - 2) = *(pointer - 2) - *(pointer - 1);
        }
        else if(c == '*')
        {
            *(pointer - 2) = *(pointer - 2) * *(pointer - 1);
        }
        else if(c == '/')
        {
            if(*(pointer - 1) == 0)
            {
                std::cout << "Error: Division by zero" << std::endl;
                return EXIT_FAILURE;
            }
            *(pointer - 2) = *(pointer - 2) / *(pointer - 1);
        }
        else if(c == '#')
        {
            break;
        }
        else
        {
            std::cout << "Error: Unknown character" << std::endl;
            return EXIT_FAILURE;
        }

        for(int* ptr = (pointer - 1); ptr < array + 79; ++ptr)
        {
            *ptr = *(ptr + 1);
        }

        if(pointer == array + 1)
        {
            std::cout << "Error: Too few operands" << std::endl;
            return EXIT_FAILURE;
        }
        --pointer;
        ++oper;
    }

    if(nums > oper + 1)
    {
        std::cout << "Error: Too few operators" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::cout << "Correct: " << *array << " is the result" << std::endl;
        return EXIT_SUCCESS;
    }
}
