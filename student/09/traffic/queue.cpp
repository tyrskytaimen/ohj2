#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here
Queue::Queue(unsigned int cycle): cycle_(cycle)
{

}

Queue::~Queue()
{
    while (first_ != nullptr)
    {
        Vehicle* item_to_delete = first_;
        first_ = first_->next;
        delete item_to_delete;
    }
}

void Queue::enqueue(string reg)
{
    if (is_green_)
    {
        std::cout << "GREEN: The vehicle "
                  << reg
                  << " need not stop to wait"
                  << std::endl;
        ++cars_passed;
        if (cars_passed == cycle_)
        {
            cars_passed = 0;
            is_green_ = false;
        }
        return;
    }

    Vehicle* new_item = new Vehicle{reg, nullptr};
    if (first_ == nullptr)
    {
        first_ = new_item;
        last_ = new_item;
    }
    else
    {
        last_->next = new_item;
        last_ = new_item;
    }
}

void Queue::print()
{
    if (is_green_ == false)
    {
        std::cout << "RED: ";
    }
    else
    {
        std::cout << "GREEN: ";
    }

    if (first_ == nullptr)
    {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
        return;
    }

    Vehicle* to_print = first_;
    std::cout << "Vehicle(s) ";
    while (to_print != nullptr)
    {
        std::cout << to_print->reg_num << " ";
        to_print = to_print->next;
    }
    std::cout << "waiting in traffic lights" << std::endl;
}

void Queue::switch_light()
{
    if (is_green_ == false)
    {
        is_green_ = true;
        if (first_ == nullptr)
        {
            print();
            return;
        }
        std::cout << "GREEN: Vehicle(s) ";
        while (dequeue())
        {
            if (cars_passed == cycle_)
            {
                std::cout << "can go on" << std::endl;
                cars_passed = 0;
                is_green_ = false;
                return;
            }
        }
        std::cout << "can go on" << std::endl;
        is_green_ = false;
    }
    else if (is_green_ == true)
    {
        is_green_ = false;
        print();
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

// Palattaa totuusarvona tiedon onko jonossa enempää autoja
bool Queue::dequeue()
{
    Vehicle* to_remove = first_;
    if (to_remove == last_)
    {
        first_ = nullptr;
        last_ = nullptr;
        ++cars_passed;
        std::cout << to_remove->reg_num << " ";
        delete to_remove;
        return false;
    }
    else
    {
        first_ = first_->next;
        ++cars_passed;
        std::cout << to_remove->reg_num << " ";
        delete to_remove;
        return true;
    }
}
