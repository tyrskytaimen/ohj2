#include "book.hh"
#include <iostream>

Book::Book(std::string author, std::string name):
    author_(author), name_(name)
{

}

void Book::print() const
{
    std::cout << author_ << " : " << name_ << std::endl;
    if (loaned_)
    {
        std::cout << "- loaned: ";
        loan_day_.print();
        std::cout << "- to be returned: ";
        return_day_.print();
    }
    else
    {
        std::cout << "- available" << std::endl;
    }
}

void Book::loan(Date& day)
{
    if (loaned_)
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
        return;
    }

    loan_day_ = day;
    return_day_ = day;
    return_day_.advance(28);
    loaned_ = true;
}

void Book::renew()
{
    if (not loaned_)
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
        return;
    }

    return_day_.advance(28);
}

void Book::give_back()
{
    if (loaned_)
    {
        loaned_ = false;
    }
}
