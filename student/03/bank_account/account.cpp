#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    name_(owner), credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << name_
              << " : "
              << iban_
              << " : "
              << balance_
              << " euros"
              << std::endl;
}

void Account::set_credit_limit(int amount)
{
    if (not credit_)
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
    else
    {
        credit_limit_ = amount;
    }
}

void Account::save_money(int amount)
{
    balance_ += amount;
}

void Account::take_money(int amount)
{
    if (enough_balance(amount))
    {
        balance_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
    }
}

void Account::transfer_to(Account& target, int amount)
{
    if (enough_balance(amount))
    {
        take_money(amount);
        target.save_money(amount);
    }
    else
    {
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }
}

bool Account::enough_balance(int amount)
{
    if (not credit_)
    {
        if (balance_ - amount < 0)
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            return false;
        }
    }
    else
    {
        if ((balance_ + credit_limit_) - amount < 0)
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            return false;
        }

    }
    return true;
}
