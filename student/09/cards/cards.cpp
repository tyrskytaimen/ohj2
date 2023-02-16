#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr), bottom_(nullptr)
{
}

// A dynamic data structure must have a destructor
// that can be called to deallocate memory,
// when the data structure is not needed any more.
Cards::~Cards()
{
    while (top_ != nullptr)
    {
        Card_data* item_to_delete = top_;
        top_ = top_->next;
        delete item_to_delete;
    }
}

// Adds a new card with the given id as the topmost element.
void Cards::add(int id)
{
    Card_data* new_item = new Card_data{id, nullptr};
    if (top_ == nullptr)
    {
        bottom_ = new_item;
        top_ = new_item;
    }
    else
    {
        new_item->next = top_;
        top_ = new_item;
    }
}

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the first element.
void Cards::print_from_top_to_bottom(std::ostream& s)
{
    int num = 1;
    Card_data* to_print = top_;
    while (to_print != nullptr)
    {
        s << num << ": " << to_print->data << std::endl;
        to_print = to_print->next;
        ++num;
    }
}

// Removes the topmost card and passes it in the reference parameter id to the caller.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::remove(int& id)
{
    if (top_ == nullptr)
    {
        return false;
    }
    Card_data* to_remove = top_;
    id = to_remove->data;
    if (to_remove == bottom_)
    {
        top_ = nullptr;
        bottom_ = nullptr;
    }
    else
    {
        top_ = top_->next;
    }
    delete to_remove;
    return true;
}

// Moves the last element of the data structure as the first one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::bottom_to_top()
{
    if (top_ == nullptr)
    {
        return false;
    }
    if (top_ == bottom_)
    {
        return true;
    }

    Card_data* to_move = top_;
    while (to_move->next != bottom_)
    {
        to_move = to_move->next;
    }
    to_move->next = nullptr;
    bottom_->next = top_;
    top_ = bottom_;
    bottom_ = to_move;

    return true;
}

// Moves the first element of the data structure as the last one.
// Returns false, if the data structure is empty, otherwise returns true.
bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
    {
        return false;
    }
    if (top_ == bottom_)
    {
        return true;
    }

    bottom_->next = top_;
    bottom_ = top_;
    top_ = top_->next;
    bottom_->next = nullptr;
    return true;
};

// Prints the content of the data structure with ordinal numbers to the
// output stream given as a parameter starting from the last element.
void Cards::print_from_bottom_to_top(std::ostream& s)
{
    s << "";
}

