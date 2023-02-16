#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  unsigned int len = s.length();
  if (len == 1 || len == 0)
  {
      return true;
  }
  else
  {
      if (s.at(0) == s.at(len-1) && palindrome_recursive(s.substr(1, len-2)))
      {
          return true;
      }
      else
      {
          return false;
      }
  }

}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
