#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <iostream>

class Book
{
public:
    Book(std::string author, std::string name);
    void print() const;
    void loan(Date& day);
    void renew();
    void give_back();

private:
    std::string author_;
    std::string name_;
    Date loan_day_;
    Date return_day_;
    bool loaned_ = false;
};

#endif // BOOK_HH
